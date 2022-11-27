# Fiber with Auth

[Postman collection](https://www.getpostman.com/collections/c862d012d5dcf50326f7)

## Endpoints

- GET /api - _Say hello_
    - POST /auth/login - _Login user_
    - GET /user/:id - _Get user_
    - POST /user - _Create user_
    - PATCH /user/:id - _Update user_
    - DELETE /user/:id - _Delete user_
    - GET /product - _Get all products_
    - GET /product/:id - _Get product_
    - POST /product - _Create product_
    - DELETE /product/:id - _Delete product_


docker run -d --name postgres-14 -p 5432:5432 -e POSTGRES_PASSWORD={password} postgres:14

https://github.com/davidpdrsn/realworld-axum-sqlx
https://github.com/an-zolkin/axum_jwt_example

docker compose up