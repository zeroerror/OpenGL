#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform float u_Time;  // 添加一个时间参数

const vec2 center = vec2(0, 0);  // 中心点坐标

void main() {
    // 平移到中心点
    vec4 centeredPos = position - vec4(center, 0.0, 0.0);

    // 计算旋转角度
    float angle = u_Time * 0.5;

    // 构造旋转矩阵
    mat4 rotationMatrix = mat4(
        vec4(cos(angle), -sin(angle), 0.0, 0.0),
        vec4(sin(angle), cos(angle), 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    // 应用旋转变换
    vec4 rotatedPos = rotationMatrix * centeredPos;

    // 平移回原来的位置
    vec4 finalPos = rotatedPos + vec4(center, 0.0, 0.0);

    gl_Position = u_MVP * finalPos;
    v_TexCoord = texCoord;
}



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_BlendColor;
uniform sampler2D u_Texture;

void main() {
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = mix(texColor, u_BlendColor, 0.618f);
}