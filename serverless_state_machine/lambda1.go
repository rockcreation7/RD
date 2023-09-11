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

func lambdaHandler1(ctx context.Context, event Event) (Result, error) {
	fmt.Printf("Received event: %+v\n", event)

	// Perform processing on the input event
	message := fmt.Sprintf("Lambda Function 1 processed: %s", event.Key1)

	result := Result{
		Message: message,
	}

	return result, nil
}

func main() {
	// Lambda function entry point (not used for Step Functions)
}

/*

In these Lambda functions:

    Each function has an Event struct that represents the expected input event structure.
    It also has a Result struct that represents the result that will be returned by the Lambda function.
    The lambdaHandler1 and lambdaHandler2 functions take the input event, perform some processing (in this case, creating a message based on the input), and return a result.
    The main function is included but not used for AWS Lambda. AWS Lambda directly invokes the designated handler functions (lambdaHandler1 and lambdaHandler2) based on the configuration you specify in your AWS Lambda settings.

Make sure to build and deploy these Lambda functions with their respective ZIP deployment packages (e.g., lambda_function_1.zip and lambda_function_2.zip) as mentioned in your Terraform configuration.

*/
