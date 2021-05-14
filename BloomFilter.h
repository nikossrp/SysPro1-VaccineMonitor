#ifndef BloomFilter_H_
#define BloomFilter_H_

#define K 16

class BloomFilter
{
    private:
        char* array;
        char* virusName;
        int bloomSize;
        void* bloomPointer;
    
    public:
        BloomFilter( char* virusName, int num);
        ~BloomFilter();
        void Insert_Record (char* str);
        bool check_Record (char* str);
        void setBit(int position);
        int get_size() { return bloomSize; }      //size of array
        char* get_virusName () const { return virusName; }
        bool checkBit(int position);
        unsigned long hash_i(char *str, int i);
};

#endif //BloomFilter_H_