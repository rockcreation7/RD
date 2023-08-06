package main

import (
	"context"
	"fmt"

	"github.com/aws/aws-lambda-go/events"
	"github.com/aws/aws-lambda-go/lambda"
	"github.com/greeeg/aws-lambda-ci-cd/pkg/message"
)

func handler(ctx context.Context, req events.APIGatewayProxyRequest) (events.APIGatewayProxyResponse, error) {

	return events.APIGatewayProxyResponse{
		StatusCode: 200,
		Body:       message.Greet("World - Data : ") + fmt.Sprintf("%+v", req),
	}, nil
}

func main() {
	lambda.Start(handler)
}
