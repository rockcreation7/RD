package main

import (
	"context"
	"runtime/trace"
	"testing"
	"time"
)

// go tool trace trace.out
// go tool pprof mem.pprof
// go tool pprof cpu.pprof
// go test -run=XXX -bench=. -benchmem -memprofile mem.pprof -cpuprofile cpu.pprof -benchtime=10s
// go test -run=XXX -bench=. -benchmem -trace traceb.out -memprofile mem.pprof -cpuprofile cpu.pprof -benchtime=10s
func BenchmarkMain(b *testing.B) {

	ctx := context.Background()
	ctx, task := trace.NewTask(ctx, "makeCappuccino")
	trace.Log(ctx, "orderID", "112333")
	hello(ctx)
	defer task.End()
}

func hello(ctx context.Context) {
	trace.WithRegion(ctx, "extractCoffee", func() { time.Sleep(time.Millisecond * 300) })
	x := []int{}
	count := 0

	for i := 0; i < 5000000; i++ {
		digi := count + (i*2/2)*100/10*1000 + 1
		x = append(x, digi)
	}

}
