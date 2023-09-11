package main

import (
	"context"
	"fmt"
)

type Event struct {
	Key1 string `json:"key1"`
	Key2 string `json:"key2"`
}

type Result struct {
	Message string `json:"message"`
}

func lambdaHandler2(ctx context.Context, event Event) (Result, error) {
	fmt.Printf("Received event: %+v\n", event)

	// Perform processing on the input event
	message := fmt.Sprintf("Lambda Function 2 processed: %s", event.Key2)

	result := Result{
		Message: message,
	}

	return result, nil
}

func main() {
	// Lambda function entry point (not used for Step Functions)
}
