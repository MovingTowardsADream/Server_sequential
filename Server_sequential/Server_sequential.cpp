#include <iostream>
#include <boost/asio.hpp>

int main()
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));

        while (true)
        {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::string message = "Connection is successful";
            boost::system::error_code ignored_error;

            // Sending a message to a user
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

            // Closes data transfer
            socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
        }
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}