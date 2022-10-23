package model

import "gorm.io/gorm"

// Wallet struct
type MemberWallet struct {
	gorm.Model
	MemberName string `gorm:"not null" json:"member_name"`
	Point      int    `gorm:"not null" json:"point"`
	ScanCode   int    `gorm:"not null" json:"scan_code"`
	Active     bool   `gorm:"not null" json:"-"`
	// User ID = OrgID
	OrgID int `gorm:"not null" json:"-"`
}

type TransactionLog struct {
	gorm.Model
	MemberName string `gorm:"not null" json:"member_name"`
	Point      int    `gorm:"not null" json:"point"`
	ScanCode   int    `gorm:"not null" json:"scan_code"`

	OrgID int `gorm:"not null" json:"-"`

	Type          int `gorm:"not null" json:"type"`
	BalanceBefore int `gorm:"not null" json:"balance_before"`
}
