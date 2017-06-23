int fread_not_move(void *ptr, int size, int nitems, FILE *stream)
{
	int num;
	if(0!=(num=fread(ptr, size, nitrms, stream)))
	{
		if(num < nitrms)
		{
			fseek(fpStream, (0 - num), SEEK_CUR);
		}
		else
		{
			fseek(fpStream, (0 - nitrms), SEEK_CUR);
		}
	}
	return num;
}

