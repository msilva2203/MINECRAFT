#pragma once

template <typename T, int W, int H, int D>
class TArray3D
{
public:
	TArray3D()
	{
		uint32_t Size = W * H * D;
		uint32_t Index = 0;
		while (Index < Size)
		{
			Buffer[Index] = {};
			Index++;
		}
	}

	T& At(int Index)
	{
		return Buffer[Index];
	}

	T& At(int X, int Y, int Z)
	{
		return Buffer[Z * W * H + Y * W + X];
	}

private:
	T Buffer[W * H * D];
};