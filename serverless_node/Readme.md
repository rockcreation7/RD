 
Test 1: 

curl "https://jfmluo4zu4.execute-api.us-east-1.amazonaws.com/dev/hello?Name=Anton"

 
Test 2: 

curl -X POST \
-H "Content-Type: application/json" \
-d '{"name":"Anton"}' \
"https://jfmluo4zu4.execute-api.us-east-1.amazonaws.com/dev/hello"

aws lambda invoke \
--region=us-east-1 \
--function-name=s3 \
--cli-binary-format raw-in-base64-out \
--payload '{"bucket":"test-alive-sparrow","object":"hello.json"}' \
response.json


https://greeeg.com/en/issues/aws-lambda-ci-cd-pipeline-github-actions-terraform

Learing From

source:
https://www.youtube.com/watch?v=bybQxpM0kSQ
https://jfmluo4zu4.execute-api.us-east-1.amazonaws.com/dev
https://antonputra.com/amazon/how-to-create-aws-lambda-with-terraform/#create-lambda-function-with-dependencies-access-to-s3-bucket