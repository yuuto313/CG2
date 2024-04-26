//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}

struct TransformationMatrix
{
    float4x4 WVP;
};

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);

struct VertexShaderOutout
{
    float4 position : SV_Position;
};

struct VertexShaderInput
{
    float4 position : POSITION0;
};

VertexShaderOutout main(VertexShaderInput input)
{
    VertexShaderOutout output;
    //mulは行列の積を求める
    output.position = mul(input.position, gTransformationMatrix.WVP);
    return output;
}