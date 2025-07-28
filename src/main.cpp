#include <stdio.h>
#include <iostream>

#include "CommonInclude.h"

int main( int argc, char* argv[] )
{
	LogDebug(__PRETTY_FUNCTION__);

    // Check for --no-window argument
    bool noWindow = false;
    for (int i = 1; i < argc; ++i)
	{
        if (std::string(argv[i]) == "--no-window")
		{
            noWindow = true;
            break;
        }
    }

    // option suppress gui window
    if (noWindow)
	{
		LogDebug("runing in the supress mode!");
    }

    TCPServer tcpServer(8080);
    std::thread tcpThread(&TCPServer::acceptClients, &tcpServer);
    
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        tcpServer.broadcastMarketData("Market Data Update\n");
    }
    
    tcpThread.join();
    
    fclose(stdout);
	return 0;
}
