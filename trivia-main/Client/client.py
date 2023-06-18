import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826

def create_message(code, my_dict, sock):
    full_str = code + "00" + str(len(my_dict)) + my_dict
    print(full_str)
    to_send = bytearray(full_str, 'utf-8')
    sock.sendall(to_send)

def main():

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    while True:
        code = input("1 for login\n2 for signup")
        if code == "1":
            username = input("enter username: ")
            password = input("enter password: ")
            login_dict = '{"username":"' + password + '","password":"' + username +'"}'
            create_message("1", login_dict, sock)
        elif code == "2":
            username = input("enter username: ")
            password = input("enter password: ")
            email = input("enter email: ")
            signup_dict = '{"username":"' + email + '","password":"' + password+'","email":"' + username + '"}'
            create_message("2", signup_dict, sock)

if __name__ == "__main__":

    main()
    pass


