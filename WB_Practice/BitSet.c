struct BitSet
{
	long int bits[4]; // allows 256 positions
};

int _bitSetIndex(int);
long int _bitSetMask(int);
void bitSetSet(int, struct BitSet);
int bitSetGet(int);
void bitSetClear(int);
void and(struct BitSet);
void or(struct BitSet);

int main()
{

	return 0;
}

int _bitSetIndex(int i)
{
	return i / 64;
}

long int _bitSetMask(int i)
{
	return 1L << (i % 64);
}

void bitSetSet(int indx, struct BitSet mySet)
{
	mySet.bits[_bitSetIndex(indx)] |= _bitSetMask(indx);
}

int bitSetGet(int indx)
{
	

}

void and(struct BitSet right)
{


}

void or(struct BitSet right)
{


}
