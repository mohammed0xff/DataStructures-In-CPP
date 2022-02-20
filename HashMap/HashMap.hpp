#pragma once


const size_t maxSize = 100;


template <typename K, typename V>
class HashNode
{

public:
	HashNode(const K& key, const V& value)
		: m_key(key)
		, m_value(value)
		, m_next(nullptr)
	{};

    K getKey() const
    {
        return m_key;
    }

    V getValue() const
    {
        return m_value;
    }

    void setValue(V value)
    {
        m_value = value;
    }

    HashNode* getNext() const
    {
        return m_next;
    }

    void setNext(HashNode* next)
    {
        m_next = next;
    }

private:
    K m_key;
    V m_value;
    HashNode* m_next;

};





template <typename K, size_t size>
struct KeyHash {
    unsigned long operator()(const K& key) const
    {
		//return reinterpret_cast<unsigned long>(key) % size;
		return key % size;
    }
};




template <typename K, typename V, size_t size = maxSize, typename hashFunction = KeyHash <K, size> >
class HashMap
{

public:
	HashMap();
	~HashMap();

	void put(const K& key, const V& value);
	const V& get(const K& key) const;
	void removeByKey(const K& key);

	// disallowing copy constructor and copy assignment operator.
    HashMap(const HashMap& other) = delete;
    const HashMap& operator=(const HashMap& other) = delete;

private:

    HashNode<K, V>* m_table[size];
    hashFunction m_hashFunction;
};




// Constructor
template <typename K, typename V, size_t size, typename hashFunction >
HashMap <K, V, size, hashFunction >::HashMap()
	: m_hashFunction()
	, m_table()
{};



// Destructor
template <typename K, typename V, size_t size, typename hashFunction >
HashMap <K, V, size, hashFunction >::~HashMap()
{
	for (size_t i = 0; i < size; ++i) {
		HashNode<K, V>* bucket = m_table[i];

		while (bucket != nullptr) {
			HashNode<K, V>* prev = bucket;
			bucket = bucket->getNext();
			delete prev;
		}
		m_table[i] = nullptr;
	}
}




// Because this is a simple HashMap, if you search for a non-existing value
// a "read access violation" Error will occur as it will reference a NULL HashNode
// unlike the standard unordered_map it returns an iterator
// to the last value existing in the array.
template <typename K, typename V, size_t size, typename hashFunction >
const V& HashMap <K, V, size, hashFunction >::get(const K& key) const
{
	unsigned long hashValue = m_hashFunction(key);
	HashNode<K, V>* bucket = m_table[hashValue];

	while (bucket != nullptr) {
		if (bucket->getKey() == key) {
			break;
		}
		bucket = bucket->getNext();
	}
	return bucket->getValue();
}




template <typename K, typename V, size_t size, typename hashFunction >
void HashMap <K, V, size, hashFunction>::put(const K& key, const V& value)
{
	unsigned long hashValue = m_hashFunction(key);
	HashNode<K, V>* bucket = m_table[hashValue];

	HashNode<K, V>* prev = nullptr;

	while (bucket != nullptr && bucket->getKey() != key) {
		prev = bucket;
		bucket = bucket->getNext();
	}

	if (bucket == nullptr) {
		bucket = new HashNode<K, V>(key, value);

		if (prev == nullptr) {
			m_table[hashValue] = bucket;
		}
		else {
			prev->setNext(bucket);
		}
	}
	else {
		bucket->setValue(value);
	}
}




template <typename K, typename V, size_t size, typename hashFunction >
void HashMap <K, V, size, hashFunction>::removeByKey(const K& key)
{
	unsigned long hashValue = m_hashFunction(key);
	HashNode<K, V>* prev = nullptr;
	HashNode<K, V>* bucket = m_table[hashValue];

	while (bucket != nullptr && bucket->getKey() != key) {
		prev = bucket;
		bucket = bucket->getNext();
	}
	// key doesn't exist
	if (bucket == nullptr) {
		return;
	}
	else {
		if (prev == nullptr) {
			m_table[hashValue] = bucket->getNext();
		}
		else {
			prev->setNext(bucket->getNext());
		}
		delete bucket;
	}
}


