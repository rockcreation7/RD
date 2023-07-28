package main

import (
	"fmt"
)

type cpuI[T any] interface {
	attack(v string) T
}

type cpu struct {
}

func (cpu cpu) attack(v string) string {
	return v
}

type Request struct {
	user   string
	amount float64
}

type robotI interface {
	recharge(request Request) string
}

type robota struct {
	cpu    cpu
	action commonAction[string]
}

func (robota robota) recharge(request Request) string {
	/// action := newCommonAction[string]()
	// s := gc.common.rechargeCommon("s", gc.sdk)
	s := robota.action.rechargeCommon("s", robota.cpu)

	return s
}

var robotList = map[string]robotI{}

func init() {
	// robotList["robota"] = initRobotI()
	setRobot("robota", initRobotI)
}

func initRobotI() robotI {
	return robota{
		action: commonAction[string]{},
		cpu:    cpu{},
	}
}

type funcSignature func() robotI

func setRobot(name string, initRobot funcSignature) {
	robotList[name] = initRobot()
}

func getRobot(name string) robotI {
	return robotList[name]
}

type commonAction[T any] struct {
}

func newCommonAction[T any]() commonAction[T] {
	return commonAction[T]{}
}

func (common commonAction[T]) rechargeCommon(user string, sdk cpuI[T]) T {
	v := sdk.attack(user)
	switch any(v).(type) {
	case string:
		fmt.Println("is string")
	}
	return v
}

func main() {
	robotI := getRobot("robota")

	res := robotI.recharge(Request{
		user:   "peter",
		amount: 10,
	})

	fmt.Println(res, " --- RES --- ")

	// recharge()
}
