#pragma once
/*
 {
      "Address": 70156504,
      "Name": "MainCamera_TypeInfo",
      "Signature": "MainCamera_c*"
    },
*/
class MainCamera
{
private:
    uint64_t Class = 0;
	uint64_t StaticClass = 0x42E80D8;
    uint64_t StaticField = 0xB8;
    uint64_t ViewMatrixOffset = 0xA8; // 	public static Matrix4x4 \u0302\u0302\u0304\u0306\u0305\u0308\u0308\u0302\u0307\u0307\u0307\u0307\u0306\u0301\u0301;
    ViewMatrix Matrix;
	public:
	MainCamera();
    void UpdateViewMatrix();
    ViewMatrix GetViewMatrix();

};