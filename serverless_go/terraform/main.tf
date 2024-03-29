terraform {
  
 
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 3.27"
    }

    archive = {
      source  = "hashicorp/archive"
      version = "~> 2.2.0"
    }
  }
 

  required_version = ">= 0.14.9"
}

provider "aws" {
  region = "us-east-1"
}