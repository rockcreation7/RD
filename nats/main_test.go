package main

import (
	"fmt"
	"testing"
	"time"

	"github.com/nats-io/nats.go"
)

var count int
// go test -v -run TestMain
func TestMain(t *testing.T) {
	nc, _ := nats.Connect(nats.DefaultURL)

	// Create JetStream Context
	js, _ := nc.JetStream()

	for{ 
		count = count+1
		time.Sleep(time.Second*1)
		js.Publish("ORDERS.scratch", []byte("count msg " + fmt.Sprintf("%d", count)))
	}
 
}