#include <iostream>
#include <string>
#include <vector>

void copydata(const uint8_t* puiVal, size_t uiSize)
{
	std::vector<uint8_t> m_oVPayload;
	m_oVPayload.resize(uiSize);

	std::copy(//std::execution::parallel_policy,
			puiVal,
			puiVal+uiSize,
			m_oVPayload.begin());
			
    int i;
    for (i=0; i<uiSize; i++)
    {
        if(puiVal[i] == m_oVPayload[i])
			std::cout << "not same" << std::endl;
    }
}

static void getBuffer(std::vector<uint8_t>& buffer, uint32_t size)
{
    int i;
    for (i=0; i<size; i++)
    {
        buffer[i]=(rand()%100)+1;
    }
}

int main()
{
	std::vector<uint8_t> buffer;
    uint32_t size = 11*1024*1024;
	buffer.resize(size);
    //uint8_t* buffer = NULL;

    getBuffer(buffer, size);
	copydata((const uint8_t*)buffer.data(), size);
}