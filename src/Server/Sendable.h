#pragma once

class Sendable {
public:
	virtual int send(void* const buf, const size_t size) = 0;

	template <class T>
	int sendPacket(T& packet) {
		return send(&packet, sizeof(T));
	}

};