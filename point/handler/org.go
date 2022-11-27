package handler

import (
	"api-fiber-gorm/database"
	"api-fiber-gorm/model"

	"github.com/gofiber/fiber/v2"
)

func CreateOrg(c *fiber.Ctx) error {
	org := &model.Org{}

	if err := c.BodyParser(org); err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Review your input", "data": err})
	}

	hash, err := hashPassword(org.Password)
	if err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Couldn't hash password", "data": err})

	}

	org.Password = hash

	if err := database.DB.Create(&org).Error; err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Couldn't create org", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "org Created", "data": org})
}

func GetOrg(c *fiber.Ctx) error {

	var orgs []model.Org

	if err := database.DB.Find(&orgs).Limit(1000).Error; err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Error on Finding orgs", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "Wallet Created", "data": orgs})
}

func CreateOrgOperator(c *fiber.Ctx) error {
	orgOperator := &model.OrgOperator{}

	if err := c.BodyParser(orgOperator); err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Review your input", "data": err})
	}

	hash, err := hashPassword(orgOperator.Password)
	if err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Couldn't hash password", "data": err})

	}
	orgOperator.Password = hash

	if err := database.DB.Create(&orgOperator).Error; err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Couldn't create org", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "org Created", "data": orgOperator})
}

func GetOrgOperator(c *fiber.Ctx) error {
	var orgOperators []model.OrgOperator

	if err := database.DB.Find(&orgOperators).Limit(1000).Error; err != nil {
		return c.Status(500).JSON(fiber.Map{"status": "error", "message": "Error on Finding orgs", "data": err})
	}

	return c.JSON(fiber.Map{"status": "success", "message": "Wallet Created", "data": orgOperators})
}
