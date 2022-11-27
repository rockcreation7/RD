package model

import "gorm.io/gorm"

// Wallet struct
type MemberWallet struct {
	gorm.Model
	MemberName string `gorm:"not null" json:"member_name"`
	Point      int    `gorm:"not null" json:"point"`
	ScanCode   int    `gorm:"not null" json:"scan_code"`
	Active     bool   `gorm:"not null" json:"-"`
	OrgID      int    `gorm:"not null" json:"-"`
	Org        Org
}
type TransactionLog struct {
	gorm.Model
	MemberName    string `gorm:"not null" json:"member_name"`
	Point         int    `gorm:"not null" json:"point"`
	ScanCode      int    `gorm:"unique_index;not null" json:"scan_code"`
	Type          int    `gorm:"not null" json:"type"`
	BalanceBefore int    `gorm:"not null" json:"balance_before"`
	OrgID         int    `gorm:"not null" json:"-"`
	Org        Org
}
