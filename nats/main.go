package main

import (
	"fmt"
	"time"

	"github.com/nats-io/nats.go"
)

func main() {

	nc, _ := nats.Connect(nats.DefaultURL)

	// Create JetStream Context
	js, _ := nc.JetStream()

	// Create a Stream
	steamInfo, err := js.AddStream(&nats.StreamConfig{
		Name:     "ORDERS",
		Subjects: []string{"ORDERS.*"},
	})

	fmt.Println("SteamInfo, err  \n", steamInfo, err, "\n SteamInfo, err ")

	_, err = js.QueueSubscribe("ORDERS.*", "job_workers", func(msg *nats.Msg) {
		fmt.Print(msg.Subject, string(msg.Data), msg.Header, "\n")
		time.Sleep(time.Microsecond * 200)
		msg.Ack()
		fmt.Println(" Msg Acked ")
	}, /* nats.Durable("MONITOR" */ nats.ManualAck(), nats.Durable("singleMONITOR"), nats.MaxAckPending(10))

	fmt.Println(err, " : err on Subscribe")
	c := make(chan int)

	<-c
}
