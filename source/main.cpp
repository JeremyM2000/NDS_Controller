/*---------------------------------------------------------------------------------

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <dswifi9.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdint.h>
#include <cstdio>
#include <string>

#include "../include/key.h"

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	struct in_addr ip, gateway, mask, dns1, dns2;

	consoleDemoInit();  //setup the sub screen for printing

	iprintf("\n\n\tSimple Wifi Connection Demo\n\n");
	iprintf("Connecting via WFC data ...\n");

	if(!Wifi_InitDefault(WFC_CONNECT)) {
		iprintf("Failed to connect!");
	} else {

		iprintf("Connected\n\n");

		ip = Wifi_GetIPInfo(&gateway, &mask, &dns1, &dns2);
		
		iprintf("ip     : %s\n", inet_ntoa(ip) );
		iprintf("gateway: %s\n", inet_ntoa(gateway) );
		iprintf("mask   : %s\n", inet_ntoa(mask) );
		iprintf("dns1   : %s\n", inet_ntoa(dns1) );
		iprintf("dns2   : %s\n", inet_ntoa(dns2) );
	}

	iprintf("----------------\n");

	//Control of input
	u32 keys_down;
	u32 keys_up;
	u32 keys_held;
	Key* keys = init_keys();
	touchPosition touch;
	char pos_x[6];
	char pos_y[6];
	keysSetRepeat(20, 5);

	// Create a TCP socket
	//char data[256];
	std::string message = "";
    int my_socket, socket_connected, c;
    my_socket = socket(AF_INET, SOCK_STREAM, 0 );

    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(9999);
    server.sin_addr.s_addr= inet_addr(inet_ntoa(ip));

	iprintf("Server Socket created : \n");
	iprintf("  - Port : 9999\n");

	bind(my_socket, (struct sockaddr*)&server, sizeof(server));
	listen(my_socket, 1);
	iprintf("Server listenning...\n");
	
	while(1) {
		c = sizeof(struct sockaddr_in);
		socket_connected = accept(my_socket, (struct sockaddr*)&client, &c);
		iprintf(" ===== Server: Connected =====\n");

		//while(recv(socket_connected, (char*)&data, sizeof(data), 0) != 0 )
		while(1)
		{
			scanKeys();
			keys_down = keysDownRepeat();
			keys_up = keysUp();
			keys_held = keysHeld();

			message = "";

			for(unsigned int i = 0; i < 12; i++)
			{
				if(keys_down & keys[i].keyValue)
				{
					message = keys[i].down;
					break;
				}

				else if(keys_up & keys[i].keyValue)
				{
					message = keys[i].up;
					break;
				}
			}
			if(message == "")
			{
				if(keys_held & KEY_TOUCH) {
					touchRead(&touch);
					sprintf(pos_x, "%04i", (touch.rawx - 184));
					sprintf(pos_y, "%04i", (touch.rawy - 200));
					message = "T_D" + std::string(pos_x) + std::string(pos_y);
				}
				else if(keys_up & KEY_TOUCH)
				{
					message = "T_U";
				}
			}

			if(message != "")
			{
				iprintf(message.c_str());
				iprintf("\n");

				if (send(socket_connected, message.c_str(), strlen(message.c_str()), 0) > 0)
					iprintf("Message sended: %s\n", message.c_str());
				else
					break;
			}

			swiWaitForVBlank();
			
			////=========================================================
			// memset(&data, 0, sizeof(data)); //clear the buffer
			// if(recv(socket_connected, (char*)&data, sizeof(data), 0) > 0)
			// {
			// 	iprintf("Message : %s\n", data);
			// }
			// else 
			// 	break;
		}

		iprintf(" === Server: Disconnected ===\n");
		//---------------------
		swiWaitForVBlank();
		scanKeys();
		keys_down = keysDown();
		if(keys_down & KEY_START)
		{
			shutdown(my_socket,0); // good practice to shutdown the socket.
			closesocket(my_socket); // remove the socket.
			break;
		}
	}

	return 0;
}
