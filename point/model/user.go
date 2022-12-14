package model

import "gorm.io/gorm"

// User struct
type User struct {
	gorm.Model
	Username string `gorm:"unique_index;not null" json:"username"`
	Email    string `gorm:"unique_index;not null" json:"email"`
	Password string `gorm:"not null" json:"password"`
	Names    string `json:"names"`
}

type Org struct {
	gorm.Model
	Orgname  string `gorm:"not null" json:"org"`
	Email    string `gorm:"unique;not null" json:"email"`
	Password string `gorm:"not null" json:"password"`
}

type OrgOperator struct {
	gorm.Model
	Username string `gorm:"unique_index;not null" json:"username"`
	Email    string `gorm:"unique_index;not null" json:"email"`
	Password string `gorm:"not null" json:"password"`
	Names    string `json:"names"`
	OrgID    int
	Org      Org
}
