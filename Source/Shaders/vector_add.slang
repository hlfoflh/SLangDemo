// Starter compute shader adapted from the official Slang hello-world example.

StructuredBuffer<float> lhs;
StructuredBuffer<float> rhs;
RWStructuredBuffer<float> output;

[shader("compute")]
[numthreads(32, 1, 1)]
void computeMain(uint3 threadId: SV_DispatchThreadID, uniform uint count)
{
    uint index = threadId.x;
    if (index >= count)
        return;

    output[index] = lhs[index] + rhs[index];
}
