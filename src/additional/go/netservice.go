package main

import "C"

import (
	"bufio"
	"fmt"
	"net"
	"strings"

	"github.com/opesun/goquery"
)

func main() {}

type Service struct {
	alive bool
}

var services = make(map[C.int]*Service)
var nextDescriptor C.int = 0

func sendResponse(conn *net.UDPConn, addr *net.UDPAddr) {
	_, err := conn.WriteToUDP([]byte("From server: Hello I got your mesage "), addr)
	if err != nil {
		fmt.Printf("Couldn't send response %v", err)
	}
}

//export go_run_server
func go_run_server() C.int {
	nextDescriptor++
	var desc C.int = nextDescriptor
	services[desc] = &Service{true}
	go go_run_server_exec(desc)
	return desc
}

func go_run_server_exec(descriptor C.int) {
	fmt.Println("service created ( descriptor:", descriptor, " )")

	p := make([]byte, 2048)
	addr := net.UDPAddr{
		Port: 1234,
		IP:   net.ParseIP("127.0.0.1"),
	}
	ser, err := net.ListenUDP("udp", &addr)
	if err != nil {
		fmt.Printf("Some error %v descriptor %d\n", err, descriptor)
		return
	}
	for services[descriptor].alive {
		_, remoteaddr, err := ser.ReadFromUDP(p)
		fmt.Printf("Read a message from %v %s descriptor %d\n", remoteaddr, p, descriptor)
		if err != nil {
			fmt.Printf("Some error  %v descriptor %d", err, descriptor)
			continue
		}
		go sendResponse(ser, remoteaddr)
	}
	fmt.Println("service closed ( descriptor:", descriptor, " )")
	delete(services, descriptor)
}

//export go_stop_service
func go_stop_service(descriptor C.int) {
	if val, ok := services[descriptor]; ok {
		val.alive = false
	}
}

//export go_test
func go_test() {
	p := make([]byte, 2048)
	conn, err := net.Dial("udp", "127.0.0.1:1234")
	if err != nil {
		fmt.Printf("Some error %v", err)
		return
	}
	fmt.Fprintf(conn, "Hi UDP Server, How are you doing?")
	_, err = bufio.NewReader(conn).Read(p)
	if err == nil {
		fmt.Printf("%s\n", p)
	} else {
		fmt.Printf("Some error %v\n", err)
	}
	conn.Close()
}

//export go_http_get
func go_http_get() {

	//resp, err := http.Get("https://music.youtube.com")
	//resp, err := http.Get("https://www.jango.com")
	//
	//if err != nil {
	//	fmt.Printf("Some error %v\n", err)
	//	return
	//}
	//
	//fmt.Println("\n\nresp:\n", resp, "\n")
	//
	//defer resp.Body.Close()
	//body, err := ioutil.ReadAll(resp.Body)
	//fmt.Println("\n\nbody:\n", body, "\n")
	//io.Copy(os.Stdout, resp.Body)

	x, err := goquery.ParseUrl("https://www.youtube.com")
	if err == nil {
		if s := strings.TrimSpace(x.Find(".fi_text").Text()); s != "" {
			fmt.Println("SSS: ", s)
		}
	}

}
