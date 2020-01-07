struct PS_IN
{
	float4 pos : SV_POSITION;
	float3 tex : TEXCOORD0;
	float4 color : COLOR0;
};

Texture2DArray textureArray : register(t0);	//読み込んだ全てのテクスチャが入っている配列
SamplerState mySampler : register(s0);		//サンプラー

float4 main(PS_IN input) : SV_Target
{
	float4 sampled = textureArray.Sample(mySampler, input.tex);
	sampled *= input.color;
	return sampled;
}