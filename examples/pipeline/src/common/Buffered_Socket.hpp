//
// Created by Romain on 23/05/2018.
//

#ifndef BUFFERED_SOCKET_HPP
#define BUFFERED_SOCKET_HPP

#include <vector>
#include <atomic>
#include <memory>
#include <aff3ct.hpp>

#include "NT_Buffered_Socket.hpp"
#include "Circular_Buffer.hpp"

template<typename T>
class Buffered_Socket : public NT_Buffered_Socket
{
public:
	Buffered_Socket(const std::vector<std::shared_ptr<aff3ct::module::Socket>> &sockets,
	                const aff3ct::module::socket_t sockets_type,
	                const size_t buffer_size);
	virtual ~Buffered_Socket();

	void  stop      (                     );
	void  reset     (                     );
	int   pop       (size_t sck_idx       );
	int   push      (size_t sck_idx       );
	void  wait_pop  (size_t sck_idx       );
	void  wait_push (size_t sck_idx       );
	void  print_data(                     );
	int   bind      (Buffered_Socket<T>* s);

	inline Circular_Buffer<T>* get_buffer() const;

protected:
	std::vector<std::vector<T>*> sockets_data;
	Circular_Buffer<T>*          buffer;

private:
	std::atomic<size_t> pop_buffer_idx;
	std::atomic<size_t> push_buffer_idx;
};

#include "Buffered_Socket.hxx"

#endif //BUFFERED_SOCKET_HPP
