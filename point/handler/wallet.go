package handler

import (
	"api-fiber-gorm/database"
	"api-fiber-gorm/model"
	"errors"

	"github.com/gofiber/fiber/v2"
	"github.com/golang-jwt/jwt/v4"
	"gorm.io/gorm"
)

func CreateWallet(c *fiber.Ctx) error {
	user := c.Locals("user").(*jwt.Token)
	claims := user.Claims.(jwt.MapClaims)

	wallet := &model.MemberWallet{}

	if err := c.BodyParser(wallet); err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Review your input", "data": err})
	}

	wallet = &model.MemberWallet{
		MemberName: wallet.MemberName,
		Point:      0,
		ScanCode:   wallet.ScanCode,
		OrgID:      int(claims["org_id"].(float64)),
	}

	if err := database.DB.Create(&wallet).Error; err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Couldn't create wallet", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "Wallet Created", "data": wallet})
}

// require super admin
func ListWallet(c *fiber.Ctx) error {
	var wallets []model.MemberWallet

	if err := database.DB.Find(&wallets).Limit(1000).Error; err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Error on Finding wallet", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "Wallet List", "data": wallets})
}

func TopUPWallet(c *fiber.Ctx) error {
	wallet := model.MemberWallet{}

	if err := c.BodyParser(wallet); err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Review your input", "data": err})
	}

	scanCode := wallet.ScanCode
	point := wallet.Point
	orgID := wallet.OrgID

	// Todo : Move to pool
	if err := database.DB.Transaction(func(tx *gorm.DB) error {
		tx.Begin()
		if err := tx.Find(&wallet).Where("scan_code =", scanCode).Where("org_id", orgID).Limit(1000).Error; err != nil {
			tx.Rollback()
			return err
		}
		// use id as unique key to find wallet
		row := tx.Exec("UPDATE member_wallet SET point = point + ? where id = ?", point, wallet.ID).Row()
		if row.Err() != nil {
			tx.Rollback()
			return row.Err()
		}
		tx.Commit()
		return nil
	}); err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Error on Updating wallet", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "Wallet Top Up", "data": wallet})
}

func deductWalletPoint(c *fiber.Ctx) error {
	wallet := model.MemberWallet{}

	if err := c.BodyParser(&wallet); err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Review your input", "data": err})
	}

	scanCode := wallet.ScanCode
	point := wallet.Point
	orgID := wallet.OrgID
	// Todo : Move to pool
	if err := database.DB.Transaction(func(tx *gorm.DB) error {
		tx.Begin()
		if err := tx.Find(&wallet).Where("scan_code =", scanCode).Where("org_id", orgID).Limit(1000).Error; err != nil {
			tx.Rollback()
			return err
		}
		// need to refactor if use sync map
		if wallet.Point-point < 0 {
			tx.Rollback()
			return errors.New("insuffienct Point")
		}
		// need to refactor if use sync map
		// use id as unique key to find wallet
		row := tx.Exec("UPDATE member_wallet SET point = point - ? where id = ?", point, wallet.ID).Row()
		if row.Err() != nil {
			tx.Rollback()
			return row.Err()
		}
		tx.Commit()
		return nil
	}); err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Error on Updating wallet", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "Wallet Deducted", "data": wallet})
}
