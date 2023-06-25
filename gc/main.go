package main

import (
	"fmt"
	"time"
)

func fibonacci(n int) []int {
	sequence := []int{}
	a, b := 0, 1
	for len(sequence) < n {
		sequence = append(sequence, a)
		a, b = b, a+b
	}
	return sequence
}

func main() {
	// Generate the first 10 Fibonacci numbers

	start := time.Now()
	fibSequence := fibonacci(100000)
	elapsed := time.Since(start)

	fmt.Println(fibSequence)
	fmt.Println("Execution time:", elapsed)
}
