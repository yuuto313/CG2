//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}

//色など三角形の表面の材質を決定するものをMaterialと呼ぶ
struct Material
{
    float4 color;
};

ConstantBuffer<Material> gMaterial : register(b0);
struct PixcelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixcelShaderOutput main()
{
    PixcelShaderOutput output;
    output.color = gMaterial.color;
    return output;
}

//02_00

//struct PixcelShaderOutput
//{
//    float32_t4 color : SV_TARGET0;
//};

//PixcelShaderOutput main()
//{
//    PixcelShaderOutput output;
//    output.color = float32_t4(1.0, 1.0, 1.0, 1.0);
//    return output;

//}