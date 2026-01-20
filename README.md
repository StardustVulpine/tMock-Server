# tMock-Server
Hobbistic project with a goal to reimplement Terraria Server with C++ and learn more about Sockets, Server Networking and Terraria Network Protocol communication.

## Status
Under development.

Current client-server communication capabilities:
- Listen for client's connections on chosen port.
- Recieve client's "Connect Request" message.
- Send Password Request to client.
- Recieves password from clent.
- Checks if password matches the one set in constexpr variable.
- Send "Fatal Error" message type to a client with a content depending on password recieved.



