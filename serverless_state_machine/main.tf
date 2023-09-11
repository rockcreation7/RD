provider "aws" {
  region = "us-east-1" # Update with your desired AWS region
}

resource "aws_iam_role" "sfn_execution_role" {
  name = "SFNExecutionRole"

  assume_role_policy = jsonencode({
    Version = "2012-10-17",
    Statement = [
      {
        Effect = "Allow",
        Principal = {
          Service = "states.amazonaws.com"
        },
        Action = "sts:AssumeRole"
      }
    ]
  })
}

resource "aws_lambda_function" "lambda_function_1" {
  function_name = "LambdaFunction1"
  runtime      = "go1.x"
  handler      = "main"
  filename     = "lambda_function_1.zip" # Path to your Lambda function code
  role         = aws_iam_role.sfn_execution_role.arn
}

resource "aws_lambda_function" "lambda_function_2" {
  function_name = "LambdaFunction2"
  runtime      = "go1.x"
  handler      = "main"
  filename     = "lambda_function_2.zip" # Path to your Lambda function code
  role         = aws_iam_role.sfn_execution_role.arn
}

resource "aws_sfn_state_machine" "example_state_machine" {
  name     = "ExampleStateMachine"
  role_arn = aws_iam_role.sfn_execution_role.arn

  definition = jsonencode({
    Comment = "An example Step Functions state machine",
    StartAt = "InvokeLambda1",
    States = {
      InvokeLambda1 = {
        Type     = "Task",
        Resource = aws_lambda_function.lambda_function_1.arn,
        End      = true,
        ResultPath = "$.result1"
      },
      InvokeLambda2 = {
        Type     = "Task",
        Resource = aws_lambda_function.lambda_function_2.arn,
        End      = true,
        ResultPath = "$.result2"
      }
    }
  })
}

locals {
  event = jsonencode({
    key1 = "value1",
    key2 = "value2"
  })
}


/* 

aws stepfunctions start-execution \
  --state-machine-arn ARN_OF_YOUR_STATE_MACHINE \
  --name EXECUTION_NAME \
  --input file://event.json


  In this command, replace "ARN_OF_YOUR_STATE_MACHINE" and "EXECUTION_NAME" with the appropriate values. The --input parameter specifies the path to a JSON file (e.g., event.json) containing your input event data. This event data will be passed to the state machine when it is invoked.

This configuration provides a clean and structured way to define the Step Functions state machine and the event object to pass between states using JSON in Terraform.


    We define an IAM role (aws_iam_role.sfn_execution_role) that Step Functions will assume to execute the Lambda functions.

    We define two Lambda functions (aws_lambda_function.lambda_function_1 and aws_lambda_function.lambda_function_2) as before, with their respective IAM roles.

    We define the Step Functions state machine (aws_sfn_state_machine.example_state_machine). The definition field uses jsonencode to define the state machine structure in JSON format.

    In the state machine definition, we include "ResultPath" for each state to capture the results of the Lambda functions and store them in the event object.

    We define a local variable event using jsonencode to specify the input event data in JSON format. This event object can be passed as input when invoking the state machine.
 */