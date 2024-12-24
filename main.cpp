#include <iostream>
#include <fstream>
#include <string>

#include <glew.h>
#include <freeglut.h>

#include <vector_matrix.h>
#include <math.h>
#include <assert.h>
using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	 -0.5f,	 0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	 -0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,	1.0f },{  0.4f, 0.4f, 0.4f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

int
CurrentWidth = 1080,
CurrentHeight = 1080;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4 model_mat_cpp;
int model_mat_location;

mat4 view_mat_cpp;
int view_mat_location;

mat4 projection_mat_cpp;
int projection_mat_location;

// ---------------------------------------------------------------------------	
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ---------------------------------------------------------------------------	
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ---------------------------------------------------------------------------	
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);

}
// ---------------------------------------------------------------------------	
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

// ---------------------------------------------------------------------------
void pavement(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0, 0.932, 0.8, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void draw_pavement()
{
	model_mat_cpp = translate(vec3(-0.148, 0.005, -0.425));
	pavement(0.01, 0.01, 0.55);
	model_mat_cpp = translate(vec3(-0.148, 0.005, 0.425));
	pavement(0.01, 0.01, 0.55);
	model_mat_cpp = translate(vec3(0.148, 0.005, 0.425));
	pavement(0.01, 0.01, 0.55);
	model_mat_cpp = translate(vec3(0.148, 0.005, -0.425));
	pavement(0.01, 0.01, 0.55);

	model_mat_cpp = translate(vec3(-0.422, 0.005, 0.148));
	pavement(0.56, 0.01, 0.01);
	model_mat_cpp = translate(vec3(0.422, 0.005, 0.148));
	pavement(0.56, 0.01, 0.01);
	model_mat_cpp = translate(vec3(-0.422, 0.005, -0.148));
	pavement(0.56, 0.01, 0.01);
	model_mat_cpp = translate(vec3(0.422, 0.005, -0.148));
	pavement(0.56, 0.01, 0.01);
}

void flat()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(1.4, 0.001, 1.4));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.662f, 0.678f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void road1()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.30, 0.021, 1.4));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void road2()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(1.4, 0.021, 0.30));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.5f, 0.5f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
float busX = 0.0f, busY = 0.0f, busZ = 0.0f;
// từ chỗ này là vẽ bus
void busBody()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.08f, 0.15f, 0.2f)); // Main body size
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.815, 0.196, 0.019, 1.0f); // Red color for the body

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void glass_bus(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(x, y, z)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.188, 0.650, 0.839, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void banhxe()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.015, 0.04, 0.04));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, 0.0, 0.0, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void noc_xe()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.075f, 0.005f, 0.19f));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.25, 0.25, 0.25, 0.8f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void mui_xe()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.07f, 0.025f, 0.01f)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, 0.0, 0.0, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void den()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.01f, 0.01f, 0.01f)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.913, 0.932, 0, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void bien_so()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.02f, 0.008f, 0.01f)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0, 1.0, 1.0, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void fender()
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(0.002f, 0.02f, 0.01f)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0, 1.0, 1.0, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void gong_guong() {
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.015f, 0.01f, 0.005f)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, 0.0, 0.0, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void guong()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.015f, 0.04f, 0.0025f)) ;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, 0.0, 0.0, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void bus()
{

	model_mat_cpp = translate(vec3(0.09, 0.1, -0.60)) * translate(vec3(busX, busY, busZ));
	busBody();
	model_mat_cpp = translate(vec3(0.09, 0.1245, -0.503)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.07f, 0.085f, 0.01f);
	model_mat_cpp = translate(vec3(0.09, 0.12, -0.701)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.07f, 0.075f, 0.01f);
	//kính bên trái
	model_mat_cpp = translate(vec3(0.052, 0.125, -0.522)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);
	model_mat_cpp = translate(vec3(0.052, 0.125, -0.572)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);
	model_mat_cpp = translate(vec3(0.052, 0.125, -0.622)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);
	model_mat_cpp = translate(vec3(0.052, 0.125, -0.672)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);


	//Kính bên phải
	model_mat_cpp = translate(vec3(0.127, 0.125, -0.522)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);
	model_mat_cpp = translate(vec3(0.127, 0.125, -0.572)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);
	model_mat_cpp = translate(vec3(0.127, 0.125, -0.622)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);
	model_mat_cpp = translate(vec3(0.127, 0.125, -0.672)) * translate(vec3(busX, busY, busZ));
	glass_bus(0.01f, 0.07f, 0.04f);

	//bánh xe bên trái
	model_mat_cpp = translate(vec3(0.048, 0.03, -0.54)) * translate(vec3(busX, busY, busZ));
	banhxe();
	model_mat_cpp = translate(vec3(0.048, 0.03, -0.66)) * translate(vec3(busX, busY, busZ));
	banhxe();
	//bánh xe bên phải
	model_mat_cpp = translate(vec3(0.134, 0.03, -0.54)) * translate(vec3(busX, busY, busZ));
	banhxe();
	model_mat_cpp = translate(vec3(0.134, 0.03, -0.66)) * translate(vec3(busX, busY, busZ));
	banhxe();

	model_mat_cpp = translate(vec3(0.09, 0.175, -0.6)) * translate(vec3(busX, busY, busZ));
	noc_xe();

	model_mat_cpp = translate(vec3(0.09, 0.037, -0.50)) * translate(vec3(busX, busY, busZ));
	mui_xe();

	model_mat_cpp = translate(vec3(0.068, 0.037, -0.497)) * translate(vec3(busX, busY, busZ));
	den();
	model_mat_cpp = translate(vec3(0.114, 0.037, -0.497)) * translate(vec3(busX, busY, busZ));
	den();

	model_mat_cpp = translate(vec3(0.092, 0.037, -0.497)) * translate(vec3(busX, busY, busZ));
	bien_so();

	model_mat_cpp = translate(vec3(0.06, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender(); 
	model_mat_cpp = translate(vec3(0.069, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender();
	model_mat_cpp = translate(vec3(0.078, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender();
	model_mat_cpp = translate(vec3(0.087, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender();
	model_mat_cpp = translate(vec3(0.096, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender();
	model_mat_cpp = translate(vec3(0.105, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender();
	model_mat_cpp = translate(vec3(0.114, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender();
	model_mat_cpp = translate(vec3(0.123, 0.067, -0.503)) * translate(vec3(busX, busY, busZ));
	fender();

	model_mat_cpp = translate(vec3(0.048, 0.125, -0.5028)) * translate(vec3(busX, busY, busZ));
	gong_guong();
	model_mat_cpp = translate(vec3(0.045, 0.125, -0.505))  * translate(vec3(busX, busY, busZ)) * rotate_y(30);
	guong();
	model_mat_cpp = translate(vec3(0.132, 0.125, -0.5028)) * translate(vec3(busX, busY, busZ));
	gong_guong();
	model_mat_cpp = translate(vec3(0.135, 0.125, -0.505))  * translate(vec3(busX, busY, busZ)) * rotate_y(-30);
	guong();
}
//--------------------------------------------------------------------------------------------
// từ chỗ này là vẽ xích đu
float xichdu_alpha = 0.0;
float swingSpeed = 0.5f;
void cot_swing()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.008, 0.10, 0.008));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.15f, 0.35f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void dinh_swing()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.1, 0.008, 0.008));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.2f, 0.15f, 0.35f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void thanhtreo_swing()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.005, 0.07, 0.008));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0f, 0.95f, 0.85f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void dayghe()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.065, 0.008, 0.03));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.35f, 0.05f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void lungghe()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.065, 0.02, 0.008));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5f, 0.35f, 0.05f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chuyendongghe() {
	model_mat_cpp = translate(vec3(-0.35, 0.105, -0.66)) * rotate_x(xichdu_alpha) * translate(vec3(0.35, -0.105, 0.66)) * translate(vec3(-0.32, 0.072, -0.66));
	thanhtreo_swing();
	model_mat_cpp = translate(vec3(-0.35, 0.105, -0.66)) * rotate_x(xichdu_alpha) * translate(vec3(0.35, -0.105, 0.66)) * translate(vec3(-0.38, 0.072, -0.66));
	thanhtreo_swing();
	model_mat_cpp = translate(vec3(-0.35, 0.105, -0.66)) * rotate_x(xichdu_alpha) * translate(vec3(0.35, -0.105, 0.66)) * translate(vec3(-0.35, 0.038, -0.66));
	dayghe();
	model_mat_cpp = translate(vec3(-0.35, 0.105, -0.66)) * rotate_x(xichdu_alpha) * translate(vec3(0.35, -0.105, 0.66)) * translate(vec3(-0.35, 0.055, -0.679)) * rotate_x(-15);
	lungghe();
}
void swing()
{
	model_mat_cpp = translate(vec3(-0.3, 0.06, -0.68)) * rotate_x(15);
	cot_swing();
	model_mat_cpp = translate(vec3(-0.3, 0.06, -0.65)) * rotate_x(-15);
	cot_swing();
	model_mat_cpp = translate(vec3(-0.4, 0.06, -0.68)) * rotate_x(15);
	cot_swing();
	model_mat_cpp = translate(vec3(-0.4, 0.06, -0.65)) * rotate_x(-15);
	cot_swing();

	model_mat_cpp = translate(vec3(-0.35, 0.105, -0.66));
	dinh_swing();
	chuyendongghe();
}

// sân pickleball
void vach_san(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 instance = identity_mat4();
	instance = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, instance.m);

	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0, 1.0, 1.0, 0.7f);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}
void nen()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.25, 0.002, 0.177));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.202f, 0.565f, 0.893f, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void luoi(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, 0.0, 0.0, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void san()
{
	model_mat_cpp = translate(vec3(-0.45, 0.006, -0.475));
	vach_san(0.005, 0.002, 0.45);
	model_mat_cpp = translate(vec3(-0.697, 0.006, -0.474));
	vach_san(0.005, 0.002, 0.45);
	model_mat_cpp = translate(vec3(-0.575, 0.006, -0.610));
	vach_san(0.005, 0.002, 0.177);
	model_mat_cpp = translate(vec3(-0.575, 0.006, -0.333));
	vach_san(0.005, 0.002, 0.177);

	model_mat_cpp = translate(vec3(-0.573, 0.006, -0.247));
	vach_san(0.25, 0.002, 0.005);
	model_mat_cpp = translate(vec3(-0.573, 0.006, -0.696));
	vach_san(0.25, 0.002, 0.005);
	model_mat_cpp = translate(vec3(-0.573, 0.006, -0.42));
	vach_san(0.25, 0.002, 0.005);
	model_mat_cpp = translate(vec3(-0.573, 0.006, -0.519));
	vach_san(0.25, 0.002, 0.005);

	model_mat_cpp = translate(vec3(-0.573, 0.005, -0.6075));
	nen();
	model_mat_cpp = translate(vec3(-0.573, 0.005, -0.3315));
	nen();

	model_mat_cpp = translate(vec3(-0.45, 0.03, -0.475));
	luoi(0.005, 0.05, 0.005);
	model_mat_cpp = translate(vec3(-0.697, 0.03, -0.475));
	luoi(0.005, 0.05, 0.005);
	model_mat_cpp = translate(vec3(-0.573, 0.056, -0.4745));
	luoi(0.25, 0.002, 0.005);
	model_mat_cpp = translate(vec3(-0.573, 0.021, -0.4745));
	luoi(0.25, 0.002, 0.005);
	model_mat_cpp = translate(vec3(-0.573, 0.030, -0.4745));
	vach_san(0.25, 0.002, 0.001);
	model_mat_cpp = translate(vec3(-0.573, 0.037, -0.4745));
	vach_san(0.25, 0.002, 0.001);
	model_mat_cpp = translate(vec3(-0.573, 0.044, -0.4745));
	vach_san(0.25, 0.002, 0.001);
	model_mat_cpp = translate(vec3(-0.573, 0.051, -0.4745));
	vach_san(0.25, 0.002, 0.001);
}

// // cây và cửa
void thancay_park()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.01, 0.03, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.380, 0.231, 0.086, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void tancay_park()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.05, 0.05, 0.05));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.047, 0.682, 0.356, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void cay_park()
{
	//1
	model_mat_cpp = translate(vec3(-0.17, 0.015, -0.68));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.68));
	tancay_park();
	//2
	model_mat_cpp = translate(vec3(-0.17, 0.015, -0.60));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.60));
	tancay_park();
	//3
	model_mat_cpp = translate(vec3(-0.17, 0.015, -0.35));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.35));
	tancay_park();
	//4
	model_mat_cpp = translate(vec3(-0.17, 0.015, -0.35));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.35));
	tancay_park();
	//5
	model_mat_cpp = translate(vec3(-0.17, 0.015, -0.27));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.27));
	tancay_park();
	//6 ************** góc **********
	model_mat_cpp = translate(vec3(-0.17, 0.015, -0.19));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.19));
	tancay_park();
	//7
	model_mat_cpp = translate(vec3(-0.255, 0.015, -0.19));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.255, 0.055, -0.19));
	tancay_park();
	//8
	model_mat_cpp = translate(vec3(-0.34, 0.015, -0.19));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.34, 0.055, -0.19));
	tancay_park();
	//9
	model_mat_cpp = translate(vec3(-0.425, 0.015, -0.19));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.425, 0.055, -0.19));
	tancay_park();
	//10
	model_mat_cpp = translate(vec3(-0.51, 0.015, -0.19));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.51, 0.055, -0.19));
	tancay_park();
	//11
	model_mat_cpp = translate(vec3(-0.595, 0.015, -0.19));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.595, 0.055, -0.19));
	tancay_park();
	//12
	model_mat_cpp = translate(vec3(-0.68, 0.015, -0.19));
	thancay_park();
	model_mat_cpp = translate(vec3(-0.68, 0.055, -0.19));
	tancay_park();
}
void cong_park(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, 0.0, 0.0, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void gate_park()
{
	// 2 thanh trụ
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.55));
	cong_park(0.008, 0.15, 0.008);
	model_mat_cpp = translate(vec3(-0.17, 0.055, -0.40));
	cong_park(0.008, 0.15, 0.008);

	// 2 cái mái
	model_mat_cpp = translate(vec3(-0.17, 0.125, -0.55)) * rotate_x(-20) * translate(vec3(0.17, -0.125, 0.55)) * translate(vec3(-0.17, 0.125, -0.515));
	cong_park(0.008, 0.008, 0.09);
	model_mat_cpp = translate(vec3(-0.17, 0.125, -0.40)) * rotate_x(20) * translate(vec3(0.17, -0.125, 0.40)) * translate(vec3(-0.17, 0.125, -0.435));
	cong_park(0.008, 0.008, 0.09);


	model_mat_cpp = translate(vec3(-0.17, 0.125, -0.475));
	cong_park(0.004, 0.004, 0.15);
	model_mat_cpp = translate(vec3(-0.17, 0.135, -0.475));
	cong_park(0.004, 0.004, 0.10);
}
// cầu trượt
void thang_cautruot()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.005, 0.12, 0.005));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, 0.0, 0.0, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void nacthang_cautruot()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.04, 0.005, 0.005));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.9, 0.8, 0.7, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void dinh_cautruot(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.7, 0.8, 0.9, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void lancan_cautruot(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6, 0.5, 0.4, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void cautruot()
{
	model_mat_cpp = translate(vec3(-0.255, 0.025, -0.27));
	thang_cautruot();
	model_mat_cpp = translate(vec3(-0.295, 0.025, -0.27));
	thang_cautruot();
	model_mat_cpp = translate(vec3(-0.255, 0.025, -0.30));
	thang_cautruot();
	model_mat_cpp = translate(vec3(-0.295, 0.025, -0.30));
	thang_cautruot();
	//
	model_mat_cpp = translate(vec3(-0.275, 0.055, -0.27));
	nacthang_cautruot();
	model_mat_cpp = translate(vec3(-0.275, 0.045, -0.27));
	nacthang_cautruot();
	model_mat_cpp = translate(vec3(-0.275, 0.035, -0.27));
	nacthang_cautruot();
	model_mat_cpp = translate(vec3(-0.275, 0.025, -0.27));
	nacthang_cautruot();
	model_mat_cpp = translate(vec3(-0.275, 0.015, -0.27));
	nacthang_cautruot();
	//
	model_mat_cpp = translate(vec3(-0.275, 0.060, -0.285));
	dinh_cautruot(0.04, 0.005, 0.04);
	model_mat_cpp = translate(vec3(-0.275, 0.055, -0.325)) * rotate_x(-35) * translate(vec3(0.275, -0.055, 0.325)) * translate(vec3(-0.275, 0.0465, -0.350));
	dinh_cautruot(0.04, 0.005, 0.1);
	model_mat_cpp = translate(vec3(-0.295, 0.065, -0.285));
	lancan_cautruot(0.003, 0.015, 0.03);
	model_mat_cpp = translate(vec3(-0.2535, 0.065, -0.285));
	lancan_cautruot(0.003, 0.015, 0.03);
	model_mat_cpp = translate(vec3(-0.275, 0.055, -0.325)) * rotate_x(-35) * translate(vec3(0.275, -0.055, 0.325)) * translate(vec3(-0.294, 0.0480, -0.349));
	lancan_cautruot(0.003, 0.015, 0.11);
	model_mat_cpp = translate(vec3(-0.275, 0.055, -0.325)) * rotate_x(-35) * translate(vec3(0.275, -0.055, 0.325)) * translate(vec3(-0.2535, 0.0480, -0.349));
	lancan_cautruot(0.003, 0.015, 0.11);
}
// xà đơn
void thanhxa(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 1.0, 0.9, 0.9, 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void xadon()
{
	model_mat_cpp = translate(vec3(-0.355, 0.025, -0.24));
	thanhxa(0.005, 0.1, 0.005);
	model_mat_cpp = translate(vec3(-0.405, 0.025, -0.24));
	thanhxa(0.005, 0.1, 0.005);
	model_mat_cpp = translate(vec3(-0.38, 0.06, -0.24));
	thanhxa(0.05, 0.005, 0.005);
}
// bập bênh
float bapbenh_alpha = 0.0;
float bapbenhSpeed = 0.5f;
void tru_bapbenh(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(x, y, z));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.0, a, 0.0, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void thanh_bapbenh()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.007, 0.005, 0.1));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.5, 0.5, 0.5, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void ghengoi_bapbenh()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.02, 0.01, 0.02));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6, 0.5, 0.8, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void lungghe_bapbenh()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.02, 0.013, 0.005));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.6, 0.5, 0.5, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void chuyendong_bapbenh()
{

	model_mat_cpp = translate(vec3(-0.38, 0.035, -0.32)) * rotate_x(bapbenh_alpha) * translate(vec3(0.38, -0.035, 0.32)) * translate(vec3(-0.38, 0.035, -0.32));
	thanh_bapbenh();
	//
	model_mat_cpp = translate(vec3(-0.38, 0.035, -0.32)) * rotate_x(bapbenh_alpha) * translate(vec3(0.38, -0.035, 0.32)) * translate(vec3(-0.38, 0.035, -0.27));
	ghengoi_bapbenh();
	model_mat_cpp = translate(vec3(-0.38, 0.035, -0.32)) * rotate_x(bapbenh_alpha) * translate(vec3(0.38, -0.035, 0.32)) * translate(vec3(-0.38, 0.035, -0.37));
	ghengoi_bapbenh();
	model_mat_cpp = translate(vec3(-0.38, 0.035, -0.32)) * rotate_x(bapbenh_alpha) * translate(vec3(0.38, -0.035, 0.32)) * translate(vec3(-0.38, 0.038, -0.38)) * rotate_x(-15);
	lungghe_bapbenh();
	model_mat_cpp = translate(vec3(-0.38, 0.035, -0.32)) * rotate_x(bapbenh_alpha) * translate(vec3(0.38, -0.035, 0.32)) * translate(vec3(-0.38, 0.038, -0.26)) * rotate_x(15);
	lungghe_bapbenh();
}

void bapbenh()
{
	model_mat_cpp = translate(vec3(-0.38, 0.01, -0.32));
	tru_bapbenh(0.007, 0.05, 0.007, 0.0);
	model_mat_cpp = translate(vec3(-0.38, 0.001, -0.32));
	tru_bapbenh(0.02, 0.02, 0.02, 0.3);
	chuyendong_bapbenh();
}

//lối đi
void nen_loidi()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.3, 0.002, 0.15));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.8f, 0.65f, 0.53f, 0.01f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void vach_loidi()
{
	mat4 gong = identity_mat4();
	gong = model_mat_cpp * scale(vec3(0.3, 0.005, 0.005));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, gong.m);
	GLint colorLocation = glGetUniformLocation(ProgramId, "objectColor");
	glUniform4f(colorLocation, 0.87, 0.72, 0.53, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void loidi()
{
	model_mat_cpp = translate(vec3(-0.3, 0.0005, -0.475));
	nen_loidi();
	model_mat_cpp = translate(vec3(-0.3, 0.0005, -0.4));
	vach_loidi();
	model_mat_cpp = translate(vec3(-0.3, 0.0005, -0.55));
	vach_loidi();
}

//------------------------------------------------------------------------------------
void park()
{
	// vẽ park
	swing();
	san();
	cay_park();
	gate_park();
	// cầu trượt
	cautruot();
	//xà
	xadon();
	//bập bênh
	bapbenh();
	//lối đi
	loidi();
}

//--------------------------------------------------------------------------------------------
float cameraX = 0.0f, cameraY = 1.5f, cameraZ = 2.1f;
float alpha = 0.0f;
float pitch = 0.7f;
float moveSpeed = 0.1f;


//-----------------------------------------------------
float
znear = 0.1f,
zfar = 100.0f,
fov = 50.0f,
aspect = (float)CurrentWidth / CurrentHeight;







void DisplayFunc(void)
{
	vec3  eye(cameraX, cameraY, cameraZ), //****************************************
		  at(cameraX + sin(alpha), cameraY - pitch, cameraZ - cos(alpha)),
		  up(0.0f, 1.0f, 0.0f);

	mat4 view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.266, 0.537, 0.894, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");

	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);



	// scene
	flat();
	road1();
	road2();
	draw_pavement();
	//bus
	bus();

	park();

	glutSwapBuffers();
}

// ---------------------------------------------------------------------------	

void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ---------------------------------------------------------------------------	

void IdleFunc(void)
{
	// TỰ động quay xích đu
	{

		xichdu_alpha += swingSpeed;

		// Đảo chiều quay khi chạm giới hạn -30 hoặc 30 độ
		if (xichdu_alpha >= 30.0f) {
			swingSpeed = -0.5f; // Đổi chiều quay về ngược lại
		}
		if (xichdu_alpha <= -30.0f) {
			swingSpeed = 0.5f; // Đổi chiều quay về xuôi
		}
		// thiết lập cờ gọi hiển thị lại
		glutPostRedisplay();
	}
	// Tự động quay bập bênh
	{
		bapbenh_alpha += bapbenhSpeed;

		// Đảo chiều quay khi chạm giới hạn -30 hoặc 30 độ
		if (bapbenh_alpha >= 30.0f) {
			bapbenhSpeed = -0.3f; // Đổi chiều quay về ngược lại
		}
		if (bapbenh_alpha <= -30.0f) {
			bapbenhSpeed = 0.3f; // Đổi chiều quay về xuôi
		}
		// thiết lập cờ gọi hiển thị lại
		glutPostRedisplay();
	}

	glutPostRedisplay();
}


// ---------------------------------------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'w':
		cameraX += sin(alpha) * moveSpeed;
		cameraZ -= cos(alpha) * moveSpeed;

		break;
	case 's':
		cameraX -= sin(alpha) * moveSpeed;
		cameraZ += cos(alpha) * moveSpeed;
		break;
	case 'd':
		cameraX += sin(alpha - 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(alpha - 3.1415926535 / 2) * moveSpeed;
		break;
	case 'a':
		cameraX += sin(alpha + 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(alpha + 3.1415926535 / 2) * moveSpeed;
		break;
	case 'q':
		pitch += 0.1f;
		break;
	case 'e':
		pitch -= 0.1f;
		break;
	case 'z':
		cameraY -= 0.1f;
		break;
	case 'x':
		cameraY += 0.1f;
		break;
	case 'j':
		alpha -= 0.1f;
		break;
	case 'k':
		alpha += 0.1f;
		break;
	case 'm':
		busZ += 0.1f;
		break;
	case 'n':
		busZ -= 0.1f;
		break;
	case 27:
		exit(EXIT_SUCCESS); break;

	}
}

// ---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Crossroad");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);

	glutCloseFunc(CloseFunc);

	glutMainLoop();

	return 0;
}
// -------------------------------------


