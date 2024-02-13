#include "Pch.h"
#include "MainCamera.h"

MainCamera::MainCamera()
{
	StaticClass = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress("GameAssembly.dll") + StaticClass);
	StaticField = TargetProcess.Read<uint64_t>(StaticClass + StaticField);

}

void MainCamera::UpdateViewMatrix()
{
	Matrix = TargetProcess.Read<ViewMatrix>(StaticClass + ViewMatrixOffset);

}
ViewMatrix MainCamera::GetViewMatrix()
{
	return Matrix;
}

