docker build -t my-golang-app .
docker run -it --rm --name my-running-app my-golang-app
docker run -it --rm -p 0.0.0.0:8080:8080 --name my-running-app my-golang-app 
docker run -it --rm -p 8080:8080 -d --name my-running-app my-golang-app 
docker push rock707/rd:my-golang-app
docker push rock707/rd:v1-release
docker tag my-golang-app:latest rock707/rd:v1-release
docker run rock707/rd:v1-release