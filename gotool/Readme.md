CPU
1. go tool pprof profile.prof
2. top

Memory
1. go tool pprof mem.prof 
2. top


1. go tool trace trace.out 
https://www.infoq.com/articles/debugging-go-programs-pprof-trace/\

web tool

1. import _ "net/http/pprof"
2. go tool pprof -http :8080 http://:6060/debug/pprof/goroutine
    
    CPU: profile?seconds=10
    Memory: heap
    Goroutines: goroutine
    Goroutine blocking: block
    Locks: mutex
    Tracing: trace?seconds=5
