package main

import (
	"errors"
	"fmt"
)

type sdkI[T any] interface {
	transfer(v string) T
}

type sdk struct {
}

func (sdk sdk) transfer(v string) string {
	return v
}

type Request struct {
	user   string
	amount float64
}

type gc[T any] struct {
	common commonAction[T]
	sdk    sdkI[T]
}

func (gc gc[string]) recharge(request Request) string {
	action := newCommonAction[string]()
	// s := gc.common.rechargeCommon("s", gc.sdk)
	s := action.rechargeCommon("s", gc.sdk)

	return s
}

type commonAction[T any] struct {
}

func newCommonAction[T any]() commonAction[T] {
	return commonAction[T]{}
}

func (common commonAction[T]) rechargeCommon(user string, sdk sdkI[T]) T {
	v := sdk.transfer(user)
	switch any(v).(type) {
	case string:
		fmt.Println("Hello")
	}
	return v
}

func rechargeSDK() (string, error) {
	return "", errors.New("TEST")
}

func main() {

	// recharge()
}
