#ifndef _INFERNO_GL_H_
#define _INFERNO_GL_H_

#include <GL/glx.h>
#include <assert.h>

#define GL_BLEND_EQUATION_RGB             0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_MAX_VARYING_FLOATS             0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE                    0x8B4F
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_SAMPLER_1D_SHADOW              0x8B61
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_DELETE_STATUS                  0x8B80
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN      0x8CA0
#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5

typedef void (*_glBlendEquationSeparate) (GLenum modeRGB, GLenum modeAlpha);
typedef void (*_glDrawBuffers) (GLsizei n, const GLenum *bufs);
typedef void (*_glStencilOpSeparate) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (*_glStencilFuncSeparate) (GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (*_glStencilMaskSeparate) (GLenum face, GLuint mask);
typedef void (*_glAttachShader) (GLuint program, GLuint shader);
typedef void (*_glBindAttribLocation) (GLuint program, GLuint index, const GLchar *name);
typedef void (*_glCompileShader) (GLuint shader);
typedef GLuint (*_glCreateProgram) (void);
typedef GLuint (*_glCreateShader) (GLenum type);
typedef void (*_glDeleteProgram) (GLuint program);
typedef void (*_glDeleteShader) (GLuint shader);
typedef void (*_glDetachShader) (GLuint program, GLuint shader);
typedef void (*_glDisableVertexAttribArray) (GLuint index);
typedef void (*_glEnableVertexAttribArray) (GLuint index);
typedef void (*_glGetActiveAttrib) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (*_glGetActiveUniform) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (*_glGetAttachedShaders) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
typedef GLint (*_glGetAttribLocation) (GLuint program, const GLchar *name);
typedef void (*_glGetProgramiv) (GLuint program, GLenum pname, GLint *params);
typedef void (*_glGetProgramInfoLog) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (*_glGetShaderiv) (GLuint shader, GLenum pname, GLint *params);
typedef void (*_glGetShaderInfoLog) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (*_glGetShaderSource) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef GLint (*_glGetUniformLocation) (GLuint program, const GLchar *name);
typedef void (*_glGetUniformfv) (GLuint program, GLint location, GLfloat *params);
typedef void (*_glGetUniformiv) (GLuint program, GLint location, GLint *params);
typedef void (*_glGetVertexAttribdv) (GLuint index, GLenum pname, GLdouble *params);
typedef void (*_glGetVertexAttribfv) (GLuint index, GLenum pname, GLfloat *params);
typedef void (*_glGetVertexAttribiv) (GLuint index, GLenum pname, GLint *params);
typedef void (*_glGetVertexAttribPointerv) (GLuint index, GLenum pname, void **pointer);
typedef GLboolean (*_glIsProgram) (GLuint program);
typedef GLboolean (*_glIsShader) (GLuint shader);
typedef void (*_glLinkProgram) (GLuint program);
typedef void (*_glShaderSource) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (*_glUseProgram) (GLuint program);
typedef void (*_glUniform1f) (GLint location, GLfloat v0);
typedef void (*_glUniform2f) (GLint location, GLfloat v0, GLfloat v1);
typedef void (*_glUniform3f) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (*_glUniform4f) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (*_glUniform1i) (GLint location, GLint v0);
typedef void (*_glUniform2i) (GLint location, GLint v0, GLint v1);
typedef void (*_glUniform3i) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (*_glUniform4i) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (*_glUniform1fv) (GLint location, GLsizei count, const GLfloat *value);
typedef void (*_glUniform2fv) (GLint location, GLsizei count, const GLfloat *value);
typedef void (*_glUniform3fv) (GLint location, GLsizei count, const GLfloat *value);
typedef void (*_glUniform4fv) (GLint location, GLsizei count, const GLfloat *value);
typedef void (*_glUniform1iv) (GLint location, GLsizei count, const GLint *value);
typedef void (*_glUniform2iv) (GLint location, GLsizei count, const GLint *value);
typedef void (*_glUniform3iv) (GLint location, GLsizei count, const GLint *value);
typedef void (*_glUniform4iv) (GLint location, GLsizei count, const GLint *value);
typedef void (*_glUniformMatrix2fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (*_glUniformMatrix3fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (*_glUniformMatrix4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (*_glValidateProgram) (GLuint program);
typedef void (*_glVertexAttrib1d) (GLuint index, GLdouble x);
typedef void (*_glVertexAttrib1dv) (GLuint index, const GLdouble *v);
typedef void (*_glVertexAttrib1f) (GLuint index, GLfloat x);
typedef void (*_glVertexAttrib1fv) (GLuint index, const GLfloat *v);
typedef void (*_glVertexAttrib1s) (GLuint index, GLshort x);
typedef void (*_glVertexAttrib1sv) (GLuint index, const GLshort *v);
typedef void (*_glVertexAttrib2d) (GLuint index, GLdouble x, GLdouble y);
typedef void (*_glVertexAttrib2dv) (GLuint index, const GLdouble *v);
typedef void (*_glVertexAttrib2f) (GLuint index, GLfloat x, GLfloat y);
typedef void (*_glVertexAttrib2fv) (GLuint index, const GLfloat *v);
typedef void (*_glVertexAttrib2s) (GLuint index, GLshort x, GLshort y);
typedef void (*_glVertexAttrib2sv) (GLuint index, const GLshort *v);
typedef void (*_glVertexAttrib3d) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (*_glVertexAttrib3dv) (GLuint index, const GLdouble *v);
typedef void (*_glVertexAttrib3f) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (*_glVertexAttrib3fv) (GLuint index, const GLfloat *v);
typedef void (*_glVertexAttrib3s) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (*_glVertexAttrib3sv) (GLuint index, const GLshort *v);
typedef void (*_glVertexAttrib4Nbv) (GLuint index, const GLbyte *v);
typedef void (*_glVertexAttrib4Niv) (GLuint index, const GLint *v);
typedef void (*_glVertexAttrib4Nsv) (GLuint index, const GLshort *v);
typedef void (*_glVertexAttrib4Nub) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (*_glVertexAttrib4Nubv) (GLuint index, const GLubyte *v);
typedef void (*_glVertexAttrib4Nuiv) (GLuint index, const GLuint *v);
typedef void (*_glVertexAttrib4Nusv) (GLuint index, const GLushort *v);
typedef void (*_glVertexAttrib4bv) (GLuint index, const GLbyte *v);
typedef void (*_glVertexAttrib4d) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (*_glVertexAttrib4dv) (GLuint index, const GLdouble *v);
typedef void (*_glVertexAttrib4f) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (*_glVertexAttrib4fv) (GLuint index, const GLfloat *v);
typedef void (*_glVertexAttrib4iv) (GLuint index, const GLint *v);
typedef void (*_glVertexAttrib4s) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (*_glVertexAttrib4sv) (GLuint index, const GLshort *v);
typedef void (*_glVertexAttrib4ubv) (GLuint index, const GLubyte *v);
typedef void (*_glVertexAttrib4uiv) (GLuint index, const GLuint *v);
typedef void (*_glVertexAttrib4usv) (GLuint index, const GLushort *v);
typedef void (*_glVertexAttribPointer) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);


typedef void (*_glBindVertexBuffer) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (*_glClipControl) (GLenum origin, GLenum depth);
typedef void (*_glCreateTransformFeedbacks) (GLsizei n, GLuint *ids);
typedef void (*_glTransformFeedbackBufferBase) (GLuint xfb, GLuint index, GLuint buffer);
typedef void (*_glTransformFeedbackBufferRange) (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (*_glGetTransformFeedbackiv) (GLuint xfb, GLenum pname, GLint *param);
typedef void (*_glGetTransformFeedbacki_v) (GLuint xfb, GLenum pname, GLuint index, GLint *param);
typedef void (*_glGetTransformFeedbacki64_v) (GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
typedef void (*_glCreateBuffers) (GLsizei n, GLuint *buffers);
typedef void (*_glNamedBufferStorage) (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (*_glNamedBufferData) (GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
typedef void (*_glNamedBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (*_glCopyNamedBufferSubData) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (*_glClearNamedBufferData) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (*_glClearNamedBufferSubData) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void* (*_glMapNamedBuffer) (GLuint buffer, GLenum access);
typedef void* (*_glMapNamedBufferRange) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef GLboolean (*_glUnmapNamedBuffer) (GLuint buffer);
typedef void (*_glFlushMappedNamedBufferRange) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (*_glGetNamedBufferParameteriv) (GLuint buffer, GLenum pname, GLint *params);
typedef void (*_glGetNamedBufferParameteri64v) (GLuint buffer, GLenum pname, GLint64 *params);
typedef void (*_glGetNamedBufferPointerv) (GLuint buffer, GLenum pname, void **params);
typedef void (*_glGetNamedBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
typedef void (*_glCreateFramebuffers) (GLsizei n, GLuint *framebuffers);
typedef void (*_glNamedFramebufferRenderbuffer) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (*_glNamedFramebufferParameteri) (GLuint framebuffer, GLenum pname, GLint param);
typedef void (*_glNamedFramebufferTexture) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (*_glNamedFramebufferTextureLayer) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (*_glNamedFramebufferDrawBuffer) (GLuint framebuffer, GLenum buf);
typedef void (*_glNamedFramebufferDrawBuffers) (GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (*_glNamedFramebufferReadBuffer) (GLuint framebuffer, GLenum src);
typedef void (*_glInvalidateNamedFramebufferData) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
typedef void (*_glInvalidateNamedFramebufferSubData) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (*_glClearNamedFramebufferiv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (*_glClearNamedFramebufferuiv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (*_glClearNamedFramebufferfv) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (*_glClearNamedFramebufferfi) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (*_glBlitNamedFramebuffer) (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (*_glCheckNamedFramebufferStatus) (GLuint framebuffer, GLenum target);
typedef void (*_glGetNamedFramebufferParameteriv) (GLuint framebuffer, GLenum pname, GLint *param);
typedef void (*_glGetNamedFramebufferAttachmentParameteriv) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (*_glCreateRenderbuffers) (GLsizei n, GLuint *renderbuffers);
typedef void (*_glNamedRenderbufferStorage) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (*_glNamedRenderbufferStorageMultisample) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (*_glGetNamedRenderbufferParameteriv) (GLuint renderbuffer, GLenum pname, GLint *params);
typedef void (*_glCreateTextures) (GLenum target, GLsizei n, GLuint *textures);
typedef void (*_glTextureBuffer) (GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (*_glTextureBufferRange) (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (*_glTextureStorage1D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (*_glTextureStorage2D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (*_glTextureStorage3D) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (*_glTextureStorage2DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (*_glTextureStorage3DMultisample) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (*_glTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (*_glTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (*_glTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (*_glCompressedTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (*_glCompressedTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (*_glCompressedTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (*_glCopyTextureSubImage1D) (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (*_glCopyTextureSubImage2D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (*_glCopyTextureSubImage3D) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (*_glTextureParameterf) (GLuint texture, GLenum pname, GLfloat param);
typedef void (*_glTextureParameterfv) (GLuint texture, GLenum pname, const GLfloat *param);
typedef void (*_glTextureParameteri) (GLuint texture, GLenum pname, GLint param);
typedef void (*_glTextureParameterIiv) (GLuint texture, GLenum pname, const GLint *params);
typedef void (*_glTextureParameterIuiv) (GLuint texture, GLenum pname, const GLuint *params);
typedef void (*_glTextureParameteriv) (GLuint texture, GLenum pname, const GLint *param);
typedef void (*_glGenerateTextureMipmap) (GLuint texture);
typedef void (*_glBindTextureUnit) (GLuint unit, GLuint texture);
typedef void (*_glGetTextureImage) (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (*_glGetCompressedTextureImage) (GLuint texture, GLint level, GLsizei bufSize, void *pixels);
typedef void (*_glGetTextureLevelParameterfv) (GLuint texture, GLint level, GLenum pname, GLfloat *params);
typedef void (*_glGetTextureLevelParameteriv) (GLuint texture, GLint level, GLenum pname, GLint *params);
typedef void (*_glGetTextureParameterfv) (GLuint texture, GLenum pname, GLfloat *params);
typedef void (*_glGetTextureParameterIiv) (GLuint texture, GLenum pname, GLint *params);
typedef void (*_glGetTextureParameterIuiv) (GLuint texture, GLenum pname, GLuint *params);
typedef void (*_glGetTextureParameteriv) (GLuint texture, GLenum pname, GLint *params);
typedef void (*_glCreateVertexArrays) (GLsizei n, GLuint *arrays);
typedef void (*_glDisableVertexArrayAttrib) (GLuint vaobj, GLuint index);
typedef void (*_glEnableVertexArrayAttrib) (GLuint vaobj, GLuint index);
typedef void (*_glVertexArrayElementBuffer) (GLuint vaobj, GLuint buffer);
typedef void (*_glVertexArrayVertexBuffer) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (*_glVertexArrayVertexBuffers) (GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
typedef void (*_glVertexArrayAttribBinding) (GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (*_glVertexArrayAttribFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (*_glVertexArrayAttribIFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (*_glVertexArrayAttribLFormat) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (*_glVertexArrayBindingDivisor) (GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (*_glGetVertexArrayiv) (GLuint vaobj, GLenum pname, GLint *param);
typedef void (*_glGetVertexArrayIndexediv) (GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (*_glGetVertexArrayIndexed64iv) (GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
typedef void (*_glCreateSamplers) (GLsizei n, GLuint *samplers);
typedef void (*_glCreateProgramPipelines) (GLsizei n, GLuint *pipelines);
typedef void (*_glCreateQueries) (GLenum target, GLsizei n, GLuint *ids);
typedef void (*_glGetQueryBufferObjecti64v) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (*_glGetQueryBufferObjectiv) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (*_glGetQueryBufferObjectui64v) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (*_glGetQueryBufferObjectuiv) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (*_glMemoryBarrierByRegion) (GLbitfield barriers);
typedef void (*_glGetTextureSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (*_glGetCompressedTextureSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
typedef void (*_glGetGraphicsResetStatus) (void);
typedef void (*_glGetnCompressedTexImage) (GLenum target, GLint lod, GLsizei bufSize, void *pixels);
typedef void (*_glGetnTexImage) (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (*_glGetnUniformdv) (GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
typedef void (*_glGetnUniformfv) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (*_glGetnUniformiv) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (*_glGetnUniformuiv) (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (*_glReadnPixels) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (*_glTextureBarrier) (void);

typedef void (*_glClearBufferData) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (*_glClearBufferSubData) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (*_glDispatchCompute) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (*_glDispatchComputeIndirect) (GLintptr indirect);
typedef void (*_glCopyImageSubData) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (*_glFramebufferParameteri) (GLenum target, GLenum pname, GLint param);
typedef void (*_glGetFramebufferParameteriv) (GLenum target, GLenum pname, GLint *params);
typedef void (*_glGetInternalformati64v) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params);
typedef void (*_glInvalidateTexSubImage) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (*_glInvalidateTexImage) (GLuint texture, GLint level);
typedef void (*_glInvalidateBufferSubData) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (*_glInvalidateBufferData) (GLuint buffer);
typedef void (*_glInvalidateFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
typedef void (*_glInvalidateSubFramebuffer) (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (*_glMultiDrawArraysIndirect) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (*_glMultiDrawElementsIndirect) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (*_glGetProgramInterfaceiv) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
typedef GLuint (*_glGetProgramResourceIndex) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (*_glGetProgramResourceName) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (*_glGetProgramResourceiv) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
typedef GLint (*_glGetProgramResourceLocation) (GLuint program, GLenum programInterface, const GLchar *name);
typedef GLint (*_glGetProgramResourceLocationIndex) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (*_glShaderStorageBlockBinding) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (*_glTexBufferRange) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (*_glTexStorage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (*_glTexStorage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (*_glTextureView) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (*_glBindVertexBuffer) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (*_glVertexAttribFormat) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (*_glVertexAttribIFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (*_glVertexAttribLFormat) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (*_glVertexAttribBinding) (GLuint attribindex, GLuint bindingindex);
typedef void (*_glVertexBindingDivisor) (GLuint bindingindex, GLuint divisor);
typedef void (*_glDebugMessageControl) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (*_glDebugMessageInsert) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (*_glDebugMessageCallback) (GLDEBUGPROC callback, const void *userParam);
typedef GLuint (*_glGetDebugMessageLog) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (*_glPushDebugGroup) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (*_glPopDebugGroup) (void);
typedef void (*_glObjectLabel) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (*_glGetObjectLabel) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (*_glObjectPtrLabel) (const void *ptr, GLsizei length, const GLchar *label);
typedef void (*_glGetObjectPtrLabel) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);

typedef void (*_glBindFragDataLocationIndexed) (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint (*_glGetFragDataIndex) (GLuint program, const GLchar *name);
typedef void (*_glGenSamplers) (GLsizei count, GLuint *samplers);
typedef void (*_glDeleteSamplers) (GLsizei count, const GLuint *samplers);
typedef GLboolean (*_glIsSampler) (GLuint sampler);
typedef void (*_glBindSampler) (GLuint unit, GLuint sampler);
typedef void (*_glSamplerParameteri) (GLuint sampler, GLenum pname, GLint param);
typedef void (*_glSamplerParameteriv) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (*_glSamplerParameterf) (GLuint sampler, GLenum pname, GLfloat param);
typedef void (*_glSamplerParameterfv) (GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (*_glSamplerParameterIiv) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (*_glSamplerParameterIuiv) (GLuint sampler, GLenum pname, const GLuint *param);
typedef void (*_glGetSamplerParameteriv) (GLuint sampler, GLenum pname, GLint *params);
typedef void (*_glGetSamplerParameterIiv) (GLuint sampler, GLenum pname, GLint *params);
typedef void (*_glGetSamplerParameterfv) (GLuint sampler, GLenum pname, GLfloat *params);
typedef void (*_glGetSamplerParameterIuiv) (GLuint sampler, GLenum pname, GLuint *params);
typedef void (*_glQueryCounter) (GLuint id, GLenum target);
typedef void (*_glGetQueryObjecti64v) (GLuint id, GLenum pname, GLint64 *params);
typedef void (*_glGetQueryObjectui64v) (GLuint id, GLenum pname, GLuint64 *params);
typedef void (*_glVertexAttribDivisor) (GLuint index, GLuint divisor);
typedef void (*_glVertexAttribP1ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (*_glVertexAttribP1uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (*_glVertexAttribP2ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (*_glVertexAttribP2uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (*_glVertexAttribP3ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (*_glVertexAttribP3uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (*_glVertexAttribP4ui) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (*_glVertexAttribP4uiv) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);

typedef void (*_glColorMaski) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (*_glGetBooleani_v) (GLenum target, GLuint index, GLboolean *data);
typedef void (*_glGetIntegeri_v) (GLenum target, GLuint index, GLint *data);
typedef void (*_glEnablei) (GLenum target, GLuint index);
typedef void (*_glDisablei) (GLenum target, GLuint index);
typedef GLboolean (*_glIsEnabledi) (GLenum target, GLuint index);
typedef void (*_glBeginTransformFeedback) (GLenum primitiveMode);
typedef void (*_glEndTransformFeedback) (void);
typedef void (*_glBindBufferRange) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (*_glBindBufferBase) (GLenum target, GLuint index, GLuint buffer);
typedef void (*_glTransformFeedbackVaryings) (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
typedef void (*_glGetTransformFeedbackVarying) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (*_glClampColor) (GLenum target, GLenum clamp);
typedef void (*_glBeginConditionalRender) (GLuint id, GLenum mode);
typedef void (*_glEndConditionalRender) (void);
typedef void (*_glVertexAttribIPointer) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (*_glGetVertexAttribIiv) (GLuint index, GLenum pname, GLint *params);
typedef void (*_glGetVertexAttribIuiv) (GLuint index, GLenum pname, GLuint *params);
typedef void (*_glVertexAttribI1i) (GLuint index, GLint x);
typedef void (*_glVertexAttribI2i) (GLuint index, GLint x, GLint y);
typedef void (*_glVertexAttribI3i) (GLuint index, GLint x, GLint y, GLint z);
typedef void (*_glVertexAttribI4i) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (*_glVertexAttribI1ui) (GLuint index, GLuint x);
typedef void (*_glVertexAttribI2ui) (GLuint index, GLuint x, GLuint y);
typedef void (*_glVertexAttribI3ui) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (*_glVertexAttribI4ui) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (*_glVertexAttribI1iv) (GLuint index, const GLint *v);
typedef void (*_glVertexAttribI2iv) (GLuint index, const GLint *v);
typedef void (*_glVertexAttribI3iv) (GLuint index, const GLint *v);
typedef void (*_glVertexAttribI4iv) (GLuint index, const GLint *v);
typedef void (*_glVertexAttribI1uiv) (GLuint index, const GLuint *v);
typedef void (*_glVertexAttribI2uiv) (GLuint index, const GLuint *v);
typedef void (*_glVertexAttribI3uiv) (GLuint index, const GLuint *v);
typedef void (*_glVertexAttribI4uiv) (GLuint index, const GLuint *v);
typedef void (*_glVertexAttribI4bv) (GLuint index, const GLbyte *v);
typedef void (*_glVertexAttribI4sv) (GLuint index, const GLshort *v);
typedef void (*_glVertexAttribI4ubv) (GLuint index, const GLubyte *v);
typedef void (*_glVertexAttribI4usv) (GLuint index, const GLushort *v);
typedef void (*_glGetUniformuiv) (GLuint program, GLint location, GLuint *params);
typedef void (*_glBindFragDataLocation) (GLuint program, GLuint color, const GLchar *name);
typedef GLint (*_glGetFragDataLocation) (GLuint program, const GLchar *name);
typedef void (*_glUniform1ui) (GLint location, GLuint v0);
typedef void (*_glUniform2ui) (GLint location, GLuint v0, GLuint v1);
typedef void (*_glUniform3ui) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (*_glUniform4ui) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (*_glUniform1uiv) (GLint location, GLsizei count, const GLuint *value);
typedef void (*_glUniform2uiv) (GLint location, GLsizei count, const GLuint *value);
typedef void (*_glUniform3uiv) (GLint location, GLsizei count, const GLuint *value);
typedef void (*_glUniform4uiv) (GLint location, GLsizei count, const GLuint *value);
typedef void (*_glTexParameterIiv) (GLenum target, GLenum pname, const GLint *params);
typedef void (*_glTexParameterIuiv) (GLenum target, GLenum pname, const GLuint *params);
typedef void (*_glGetTexParameterIiv) (GLenum target, GLenum pname, GLint *params);
typedef void (*_glGetTexParameterIuiv) (GLenum target, GLenum pname, GLuint *params);
typedef void (*_glClearBufferiv) (GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (*_glClearBufferuiv) (GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (*_glClearBufferfv) (GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (*_glClearBufferfi) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);

typedef const GLubyte* (*_glGetStringi) (GLenum name, GLuint index);
typedef GLboolean (*_glIsRenderbuffer) (GLuint renderbuffer);
typedef void (*_glBindRenderbuffer) (GLenum target, GLuint renderbuffer);
typedef void (*_glDeleteRenderbuffers) (GLsizei n, const GLuint *renderbuffers);
typedef void (*_glGenRenderbuffers) (GLsizei n, GLuint *renderbuffers);
typedef void (*_glRenderbufferStorage) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (*_glGetRenderbufferParameteriv) (GLenum target, GLenum pname, GLint *params);
typedef GLboolean (*_glIsFramebuffer) (GLuint framebuffer);
typedef void (*_glBindFramebuffer) (GLenum target, GLuint framebuffer);
typedef void (*_glDeleteFramebuffers) (GLsizei n, const GLuint *framebuffers);
typedef void (*_glGenFramebuffers) (GLsizei n, GLuint *framebuffers);
typedef GLenum (*_glCheckFramebufferStatus) (GLenum target);
typedef void (*_glFramebufferTexture1D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (*_glFramebufferTexture2D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (*_glFramebufferTexture3D) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (*_glFramebufferRenderbuffer) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (*_glGetFramebufferAttachmentParameteriv) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (*_glGenerateMipmap) (GLenum target);
typedef void (*_glBlitFramebuffer) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (*_glRenderbufferStorageMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (*_glFramebufferTextureLayer) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);

typedef void* (*_glMapBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (*_glFlushMappedBufferRange) (GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (*_glBindVertexArray) (GLuint array);
typedef void (*_glDeleteVertexArrays) (GLsizei n, const GLuint *arrays);
typedef void (*_glGenVertexArrays) (GLsizei n, GLuint *arrays);
typedef GLboolean (*_glIsVertexArray) (GLuint array);

typedef void (*_glGenQueries) (GLsizei n, GLuint *ids);
typedef void (*_glDeleteQueries) (GLsizei n, const GLuint *ids);
typedef GLboolean (*_glIsQuery) (GLuint id);
typedef void (*_glBeginQuery) (GLenum target, GLuint id);
typedef void (*_glEndQuery) (GLenum target);
typedef void (*_glGetQueryiv) (GLenum target, GLenum pname, GLint *params);
typedef void (*_glGetQueryObjectiv) (GLuint id, GLenum pname, GLint *params);
typedef void (*_glGetQueryObjectuiv) (GLuint id, GLenum pname, GLuint *params);
typedef void (*_glBindBuffer) (GLenum target, GLuint buffer);
typedef void (*_glDeleteBuffers) (GLsizei n, const GLuint *buffers);
typedef void (*_glGenBuffers) (GLsizei n, GLuint *buffers);
typedef GLboolean (*_glIsBuffer) (GLuint buffer);
typedef void (*_glBufferData) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (*_glBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (*_glGetBufferSubData) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
typedef void* (*_glMapBuffer) (GLenum target, GLenum access);
typedef GLboolean (*_glUnmapBuffer) (GLenum target);
typedef void (*_glGetBufferParameteriv) (GLenum target, GLenum pname, GLint *params);
typedef void (*_glGetBufferPointerv) (GLenum target, GLenum pname, void **params);

typedef void (*_glDrawElementsBaseVertex) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (*_glDrawRangeElementsBaseVertex) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (*_glDrawElementsInstancedBaseVertex) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
typedef void (*_glMultiDrawElementsBaseVertex) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
typedef void (*_glProvokingVertex) (GLenum mode);
typedef GLsync (*_glFenceSync) (GLenum condition, GLbitfield flags);
typedef GLboolean (*_glIsSync) (GLsync sync);
typedef void (*_glDeleteSync) (GLsync sync);
typedef GLenum (*_glClientWaitSync) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (*_glWaitSync) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (*_glGetInteger64v) (GLenum pname, GLint64 *data);
typedef void (*_glGetSynciv) (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
typedef void (*_glGetInteger64i_v) (GLenum target, GLuint index, GLint64 *data);
typedef void (*_glGetBufferParameteri64v) (GLenum target, GLenum pname, GLint64 *params);
typedef void (*_glFramebufferTexture) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (*_glTexImage2DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (*_glTexImage3DMultisample) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (*_glGetMultisamplefv) (GLenum pname, GLuint index, GLfloat *val);
typedef void (*_glSampleMaski) (GLuint maskNumber, GLbitfield mask);

typedef void (*_glMinSampleShading) (GLfloat value);
typedef void (*_glBlendEquationi) (GLuint buf, GLenum mode);
typedef void (*_glBlendEquationSeparatei) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (*_glBlendFunci) (GLuint buf, GLenum src, GLenum dst);
typedef void (*_glBlendFuncSeparatei) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (*_glDrawArraysIndirect) (GLenum mode, const void *indirect);
typedef void (*_glDrawElementsIndirect) (GLenum mode, GLenum type, const void *indirect);
typedef void (*_glUniform1d) (GLint location, GLdouble x);
typedef void (*_glUniform2d) (GLint location, GLdouble x, GLdouble y);
typedef void (*_glUniform3d) (GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (*_glUniform4d) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (*_glUniform1dv) (GLint location, GLsizei count, const GLdouble *value);
typedef void (*_glUniform2dv) (GLint location, GLsizei count, const GLdouble *value);
typedef void (*_glUniform3dv) (GLint location, GLsizei count, const GLdouble *value);
typedef void (*_glUniform4dv) (GLint location, GLsizei count, const GLdouble *value);
typedef void (*_glUniformMatrix2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix2x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix2x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix3x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix3x4dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix4x2dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glUniformMatrix4x3dv) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (*_glGetUniformdv) (GLuint program, GLint location, GLdouble *params);
typedef GLint (*_glGetSubroutineUniformLocation) (GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint (*_glGetSubroutineIndex) (GLuint program, GLenum shadertype, const GLchar *name);
typedef void (*_glGetActiveSubroutineUniformiv) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (*_glGetActiveSubroutineUniformName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (*_glGetActiveSubroutineName) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name);
typedef void (*_glUniformSubroutinesuiv) (GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (*_glGetUniformSubroutineuiv) (GLenum shadertype, GLint location, GLuint *params);
typedef void (*_glGetProgramStageiv) (GLuint program, GLenum shadertype, GLenum pname, GLint *values);
typedef void (*_glPatchParameteri) (GLenum pname, GLint value);
typedef void (*_glPatchParameterfv) (GLenum pname, const GLfloat *values);
typedef void (*_glBindTransformFeedback) (GLenum target, GLuint id);
typedef void (*_glDeleteTransformFeedbacks) (GLsizei n, const GLuint *ids);
typedef void (*_glGenTransformFeedbacks) (GLsizei n, GLuint *ids);
typedef GLboolean (*_glIsTransformFeedback) (GLuint id);
typedef void (*_glPauseTransformFeedback) (void);
typedef void (*_glResumeTransformFeedback) (void);
typedef void (*_glDrawTransformFeedback) (GLenum mode, GLuint id);
typedef void (*_glDrawTransformFeedbackStream) (GLenum mode, GLuint id, GLuint stream);
typedef void (*_glBeginQueryIndexed) (GLenum target, GLuint index, GLuint id);
typedef void (*_glEndQueryIndexed) (GLenum target, GLuint index);
typedef void (*_glGetQueryIndexediv) (GLenum target, GLuint index, GLenum pname, GLint *params);

typedef void (*_glBlendEquationiARB) (GLuint buf, GLenum mode);
typedef void (*_glBlendEquationSeparateiARB) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (*_glBlendFunciARB) (GLuint buf, GLenum src, GLenum dst);
typedef void (*_glBlendFuncSeparateiARB) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);

typedef void (*_glBlendFuncSeparate) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (*_glMultiDrawArrays) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
typedef void (*_glMultiDrawElements) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
typedef void (*_glPointParameterf) (GLenum pname, GLfloat param);
typedef void (*_glPointParameterfv) (GLenum pname, const GLfloat *params);
typedef void (*_glPointParameteri) (GLenum pname, GLint param);
typedef void (*_glPointParameteriv) (GLenum pname, const GLint *params);
typedef void (*_glBlendColor) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (*_glBlendEquation) (GLenum mode);

extern _glBlendFuncSeparate _inferno_glBlendFuncSeparate;
#define glBlendFuncSeparate _inferno_glBlendFuncSeparate
extern _glMultiDrawArrays _inferno_glMultiDrawArrays;
#define glMultiDrawArrays _inferno_glMultiDrawArrays
extern _glMultiDrawElements _inferno_glMultiDrawElements;
#define glMultiDrawElements _inferno_glMultiDrawElements
extern _glPointParameterf _inferno_glPointParameterf;
#define glPointParameterf _inferno_glPointParameterf
extern _glPointParameterfv _inferno_glPointParameterfv;
#define glPointParameterfv _inferno_glPointParameterfv
extern _glPointParameteri _inferno_glPointParameteri;
#define glPointParameteri _inferno_glPointParameteri
extern _glPointParameteriv _inferno_glPointParameteriv;
#define glPointParameteriv _inferno_glPointParameteriv
extern _glBlendColor _inferno_glBlendColor;
#define glBlendColor _inferno_glBlendColor
extern _glBlendEquation _inferno_glBlendEquation;
#define glBlendEquation _inferno_glBlendEquation

extern _glBlendEquationiARB _inferno_glBlendEquationiARB;
#define glBlendEquationiARB _inferno_glBlendEquationiARB
extern _glBlendEquationSeparateiARB _inferno_glBlendEquationSeparateiARB;
#define glBlendEquationSeparateiARB _inferno_glBlendEquationSeparateiARB
extern _glBlendFunciARB _inferno_glBlendFunciARB;
#define glBlendFunciARB _inferno_glBlendFunciARB
extern _glBlendFuncSeparateiARB _inferno_glBlendFuncSeparateiARB;
#define glBlendFuncSeparateiARB _inferno_glBlendFuncSeparateiARB

extern _glMinSampleShading _inferno_glMinSampleShading;
#define glMinSampleShading _inferno_glMinSampleShading
extern _glBlendEquationi _inferno_glBlendEquationi;
#define glBlendEquationi _inferno_glBlendEquationi
extern _glBlendEquationSeparatei _inferno_glBlendEquationSeparatei;
#define glBlendEquationSeparatei _inferno_glBlendEquationSeparatei
extern _glBlendFunci _inferno_glBlendFunci;
#define glBlendFunci _inferno_glBlendFunci
extern _glBlendFuncSeparatei _inferno_glBlendFuncSeparatei;
#define glBlendFuncSeparatei _inferno_glBlendFuncSeparatei
extern _glDrawArraysIndirect _inferno_glDrawArraysIndirect;
#define glDrawArraysIndirect _inferno_glDrawArraysIndirect
extern _glDrawElementsIndirect _inferno_glDrawElementsIndirect;
#define glDrawElementsIndirect _inferno_glDrawElementsIndirect
extern _glUniform1d _inferno_glUniform1d;
#define glUniform1d _inferno_glUniform1d
extern _glUniform2d _inferno_glUniform2d;
#define glUniform2d _inferno_glUniform2d
extern _glUniform3d _inferno_glUniform3d;
#define glUniform3d _inferno_glUniform3d
extern _glUniform4d _inferno_glUniform4d;
#define glUniform4d _inferno_glUniform4d
extern _glUniform1dv _inferno_glUniform1dv;
#define glUniform1dv _inferno_glUniform1dv
extern _glUniform2dv _inferno_glUniform2dv;
#define glUniform2dv _inferno_glUniform2dv
extern _glUniform3dv _inferno_glUniform3dv;
#define glUniform3dv _inferno_glUniform3dv
extern _glUniform4dv _inferno_glUniform4dv;
#define glUniform4dv _inferno_glUniform4dv
extern _glUniformMatrix2dv _inferno_glUniformMatrix2dv;
#define glUniformMatrix2dv _inferno_glUniformMatrix2dv
extern _glUniformMatrix3dv _inferno_glUniformMatrix3dv;
#define glUniformMatrix3dv _inferno_glUniformMatrix3dv
extern _glUniformMatrix4dv _inferno_glUniformMatrix4dv;
#define glUniformMatrix4dv _inferno_glUniformMatrix4dv
extern _glUniformMatrix2x3dv _inferno_glUniformMatrix2x3dv;
#define glUniformMatrix2x3dv _inferno_glUniformMatrix2x3dv
extern _glUniformMatrix2x4dv _inferno_glUniformMatrix2x4dv;
#define glUniformMatrix2x4dv _inferno_glUniformMatrix2x4dv
extern _glUniformMatrix3x2dv _inferno_glUniformMatrix3x2dv;
#define glUniformMatrix3x2dv _inferno_glUniformMatrix3x2dv
extern _glUniformMatrix3x4dv _inferno_glUniformMatrix3x4dv;
#define glUniformMatrix3x4dv _inferno_glUniformMatrix3x4dv
extern _glUniformMatrix4x2dv _inferno_glUniformMatrix4x2dv;
#define glUniformMatrix4x2dv _inferno_glUniformMatrix4x2dv
extern _glUniformMatrix4x3dv _inferno_glUniformMatrix4x3dv;
#define glUniformMatrix4x3dv _inferno_glUniformMatrix4x3dv
extern _glGetUniformdv _inferno_glGetUniformdv;
#define glGetUniformdv _inferno_glGetUniformdv
extern _glGetSubroutineUniformLocation _inferno_glGetSubroutineUniformLocation;
#define glGetSubroutineUniformLocation _inferno_glGetSubroutineUniformLocation
extern _glGetSubroutineIndex _inferno_glGetSubroutineIndex;
#define glGetSubroutineIndex _inferno_glGetSubroutineIndex
extern _glGetActiveSubroutineUniformiv _inferno_glGetActiveSubroutineUniformiv;
#define glGetActiveSubroutineUniformiv _inferno_glGetActiveSubroutineUniformiv
extern _glGetActiveSubroutineUniformName _inferno_glGetActiveSubroutineUniformName;
#define glGetActiveSubroutineUniformName _inferno_glGetActiveSubroutineUniformName
extern _glGetActiveSubroutineName _inferno_glGetActiveSubroutineName;
#define glGetActiveSubroutineName _inferno_glGetActiveSubroutineName
extern _glUniformSubroutinesuiv _inferno_glUniformSubroutinesuiv;
#define glUniformSubroutinesuiv _inferno_glUniformSubroutinesuiv
extern _glGetUniformSubroutineuiv _inferno_glGetUniformSubroutineuiv;
#define glGetUniformSubroutineuiv _inferno_glGetUniformSubroutineuiv
extern _glGetProgramStageiv _inferno_glGetProgramStageiv;
#define glGetProgramStageiv _inferno_glGetProgramStageiv
extern _glPatchParameteri _inferno_glPatchParameteri;
#define glPatchParameteri _inferno_glPatchParameteri
extern _glPatchParameterfv _inferno_glPatchParameterfv;
#define glPatchParameterfv _inferno_glPatchParameterfv
extern _glBindTransformFeedback _inferno_glBindTransformFeedback;
#define glBindTransformFeedback _inferno_glBindTransformFeedback
extern _glDeleteTransformFeedbacks _inferno_glDeleteTransformFeedbacks;
#define glDeleteTransformFeedbacks _inferno_glDeleteTransformFeedbacks
extern _glGenTransformFeedbacks _inferno_glGenTransformFeedbacks;
#define glGenTransformFeedbacks _inferno_glGenTransformFeedbacks
extern _glIsTransformFeedback _inferno_glIsTransformFeedback;
#define glIsTransformFeedback _inferno_glIsTransformFeedback
extern _glPauseTransformFeedback _inferno_glPauseTransformFeedback;
#define glPauseTransformFeedback _inferno_glPauseTransformFeedback
extern _glResumeTransformFeedback _inferno_glResumeTransformFeedback;
#define glResumeTransformFeedback _inferno_glResumeTransformFeedback
extern _glDrawTransformFeedback _inferno_glDrawTransformFeedback;
#define glDrawTransformFeedback _inferno_glDrawTransformFeedback
extern _glDrawTransformFeedbackStream _inferno_glDrawTransformFeedbackStream;
#define glDrawTransformFeedbackStream _inferno_glDrawTransformFeedbackStream
extern _glBeginQueryIndexed _inferno_glBeginQueryIndexed;
#define glBeginQueryIndexed _inferno_glBeginQueryIndexed
extern _glEndQueryIndexed _inferno_glEndQueryIndexed;
#define glEndQueryIndexed _inferno_glEndQueryIndexed
extern _glGetQueryIndexediv _inferno_glGetQueryIndexediv;
#define glGetQueryIndexediv _inferno_glGetQueryIndexediv

extern _glDrawElementsBaseVertex _inferno_glDrawElementsBaseVertex;
#define glDrawElementsBaseVertex _inferno_glDrawElementsBaseVertex
extern _glDrawRangeElementsBaseVertex _inferno_glDrawRangeElementsBaseVertex;
#define glDrawRangeElementsBaseVertex _inferno_glDrawRangeElementsBaseVertex
extern _glDrawElementsInstancedBaseVertex _inferno_glDrawElementsInstancedBaseVertex;
#define glDrawElementsInstancedBaseVertex _inferno_glDrawElementsInstancedBaseVertex
extern _glMultiDrawElementsBaseVertex _inferno_glMultiDrawElementsBaseVertex;
#define glMultiDrawElementsBaseVertex _inferno_glMultiDrawElementsBaseVertex
extern _glProvokingVertex _inferno_glProvokingVertex;
#define glProvokingVertex _inferno_glProvokingVertex
extern _glFenceSync _inferno_glFenceSync;
#define glFenceSync _inferno_glFenceSync
extern _glIsSync _inferno_glIsSync;
#define glIsSync _inferno_glIsSync
extern _glDeleteSync _inferno_glDeleteSync;
#define glDeleteSync _inferno_glDeleteSync
extern _glClientWaitSync _inferno_glClientWaitSync;
#define glClientWaitSync _inferno_glClientWaitSync
extern _glWaitSync _inferno_glWaitSync;
#define glWaitSync _inferno_glWaitSync
extern _glGetInteger64v _inferno_glGetInteger64v;
#define glGetInteger64v _inferno_glGetInteger64v
extern _glGetSynciv _inferno_glGetSynciv;
#define glGetSynciv _inferno_glGetSynciv
extern _glGetInteger64i_v _inferno_glGetInteger64i_v;
#define glGetInteger64i_v _inferno_glGetInteger64i_v
extern _glGetBufferParameteri64v _inferno_glGetBufferParameteri64v;
#define glGetBufferParameteri64v _inferno_glGetBufferParameteri64v
extern _glFramebufferTexture _inferno_glFramebufferTexture;
#define glFramebufferTexture _inferno_glFramebufferTexture
extern _glTexImage2DMultisample _inferno_glTexImage2DMultisample;
#define glTexImage2DMultisample _inferno_glTexImage2DMultisample
extern _glTexImage3DMultisample _inferno_glTexImage3DMultisample;
#define glTexImage3DMultisample _inferno_glTexImage3DMultisample
extern _glGetMultisamplefv _inferno_glGetMultisamplefv;
#define glGetMultisamplefv _inferno_glGetMultisamplefv
extern _glSampleMaski _inferno_glSampleMaski;
#define glSampleMaski _inferno_glSampleMaski

extern _glGenQueries _inferno_glGenQueries;
#define glGenQueries _inferno_glGenQueries
extern _glDeleteQueries _inferno_glDeleteQueries;
#define glDeleteQueries _inferno_glDeleteQueries
extern _glIsQuery _inferno_glIsQuery;
#define glIsQuery _inferno_glIsQuery
extern _glBeginQuery _inferno_glBeginQuery;
#define glBeginQuery _inferno_glBeginQuery
extern _glEndQuery _inferno_glEndQuery;
#define glEndQuery _inferno_glEndQuery
extern _glGetQueryiv _inferno_glGetQueryiv;
#define glGetQueryiv _inferno_glGetQueryiv
extern _glGetQueryObjectiv _inferno_glGetQueryObjectiv;
#define glGetQueryObjectiv _inferno_glGetQueryObjectiv
extern _glGetQueryObjectuiv _inferno_glGetQueryObjectuiv;
#define glGetQueryObjectuiv _inferno_glGetQueryObjectuiv
extern _glBindBuffer _inferno_glBindBuffer;
#define glBindBuffer _inferno_glBindBuffer
extern _glDeleteBuffers _inferno_glDeleteBuffers;
#define glDeleteBuffers _inferno_glDeleteBuffers
extern _glGenBuffers _inferno_glGenBuffers;
#define glGenBuffers _inferno_glGenBuffers
extern _glIsBuffer _inferno_glIsBuffer;
#define glIsBuffer _inferno_glIsBuffer
extern _glBufferData _inferno_glBufferData;
#define glBufferData _inferno_glBufferData
extern _glBufferSubData _inferno_glBufferSubData;
#define glBufferSubData _inferno_glBufferSubData
extern _glGetBufferSubData _inferno_glGetBufferSubData;
#define glGetBufferSubData _inferno_glGetBufferSubData
extern _glMapBuffer _inferno_glMapBuffer;
#define glMapBuffer _inferno_glMapBuffer
extern _glUnmapBuffer _inferno_glUnmapBuffer;
#define glUnmapBuffer _inferno_glUnmapBuffer
extern _glGetBufferParameteriv _inferno_glGetBufferParameteriv;
#define glGetBufferParameteriv _inferno_glGetBufferParameteriv
extern _glGetBufferPointerv _inferno_glGetBufferPointerv;
#define glGetBufferPointerv _inferno_glGetBufferPointerv

extern _glBindFragDataLocationIndexed _inferno_glBindFragDataLocationIndexed;
#define glBindFragDataLocationIndexed _inferno_glBindFragDataLocationIndexed
extern _glGetFragDataIndex _inferno_glGetFragDataIndex;
#define glGetFragDataIndex _inferno_glGetFragDataIndex
extern _glGenSamplers _inferno_glGenSamplers;
#define glGenSamplers _inferno_glGenSamplers
extern _glDeleteSamplers _inferno_glDeleteSamplers;
#define glDeleteSamplers _inferno_glDeleteSamplers
extern _glIsSampler _inferno_glIsSampler;
#define glIsSampler _inferno_glIsSampler
extern _glBindSampler _inferno_glBindSampler;
#define glBindSampler _inferno_glBindSampler
extern _glSamplerParameteri _inferno_glSamplerParameteri;
#define glSamplerParameteri _inferno_glSamplerParameteri
extern _glSamplerParameteriv _inferno_glSamplerParameteriv;
#define glSamplerParameteriv _inferno_glSamplerParameteriv
extern _glSamplerParameterf _inferno_glSamplerParameterf;
#define glSamplerParameterf _inferno_glSamplerParameterf
extern _glSamplerParameterfv _inferno_glSamplerParameterfv;
#define glSamplerParameterfv _inferno_glSamplerParameterfv
extern _glSamplerParameterIiv _inferno_glSamplerParameterIiv;
#define glSamplerParameterIiv _inferno_glSamplerParameterIiv
extern _glSamplerParameterIuiv _inferno_glSamplerParameterIuiv;
#define glSamplerParameterIuiv _inferno_glSamplerParameterIuiv
extern _glGetSamplerParameteriv _inferno_glGetSamplerParameteriv;
#define glGetSamplerParameteriv _inferno_glGetSamplerParameteriv
extern _glGetSamplerParameterIiv _inferno_glGetSamplerParameterIiv;
#define glGetSamplerParameterIiv _inferno_glGetSamplerParameterIiv
extern _glGetSamplerParameterfv _inferno_glGetSamplerParameterfv;
#define glGetSamplerParameterfv _inferno_glGetSamplerParameterfv
extern _glGetSamplerParameterIuiv _inferno_glGetSamplerParameterIuiv;
#define glGetSamplerParameterIuiv _inferno_glGetSamplerParameterIuiv
extern _glQueryCounter _inferno_glQueryCounter;
#define glQueryCounter _inferno_glQueryCounter
extern _glGetQueryObjecti64v _inferno_glGetQueryObjecti64v;
#define glGetQueryObjecti64v _inferno_glGetQueryObjecti64v
extern _glGetQueryObjectui64v _inferno_glGetQueryObjectui64v;
#define glGetQueryObjectui64v _inferno_glGetQueryObjectui64v
extern _glVertexAttribDivisor _inferno_glVertexAttribDivisor;
#define glVertexAttribDivisor _inferno_glVertexAttribDivisor
extern _glVertexAttribP1ui _inferno_glVertexAttribP1ui;
#define glVertexAttribP1ui _inferno_glVertexAttribP1ui
extern _glVertexAttribP1uiv _inferno_glVertexAttribP1uiv;
#define glVertexAttribP1uiv _inferno_glVertexAttribP1uiv
extern _glVertexAttribP2ui _inferno_glVertexAttribP2ui;
#define glVertexAttribP2ui _inferno_glVertexAttribP2ui
extern _glVertexAttribP2uiv _inferno_glVertexAttribP2uiv;
#define glVertexAttribP2uiv _inferno_glVertexAttribP2uiv
extern _glVertexAttribP3ui _inferno_glVertexAttribP3ui;
#define glVertexAttribP3ui _inferno_glVertexAttribP3ui
extern _glVertexAttribP3uiv _inferno_glVertexAttribP3uiv;
#define glVertexAttribP3uiv _inferno_glVertexAttribP3uiv
extern _glVertexAttribP4ui _inferno_glVertexAttribP4ui;
#define glVertexAttribP4ui _inferno_glVertexAttribP4ui
extern _glVertexAttribP4uiv _inferno_glVertexAttribP4uiv;
#define glVertexAttribP4uiv _inferno_glVertexAttribP4uiv

extern _glBlendEquationSeparate _inferno_glBlendEquationSeparate;
#define glBlendEquationSeparate _inferno_glBlendEquationSeparate
extern _glDrawBuffers _inferno_glDrawBuffers;
#define glDrawBuffers _inferno_glDrawBuffers
extern _glStencilOpSeparate _inferno_glStencilOpSeparate;
#define glStencilOpSeparate _inferno_glStencilOpSeparate
extern _glStencilFuncSeparate _inferno_glStencilFuncSeparate;
#define glStencilFuncSeparate _inferno_glStencilFuncSeparate
extern _glStencilMaskSeparate _inferno_glStencilMaskSeparate;
#define glStencilMaskSeparate _inferno_glStencilMaskSeparate
extern _glAttachShader _inferno_glAttachShader;
#define glAttachShader _inferno_glAttachShader
extern _glBindAttribLocation _inferno_glBindAttribLocation;
#define glBindAttribLocation _inferno_glBindAttribLocation
extern _glCompileShader _inferno_glCompileShader;
#define glCompileShader _inferno_glCompileShader
extern _glCreateProgram _inferno_glCreateProgram;
#define glCreateProgram _inferno_glCreateProgram
extern _glCreateShader _inferno_glCreateShader;
#define glCreateShader _inferno_glCreateShader
extern _glDeleteProgram _inferno_glDeleteProgram;
#define glDeleteProgram _inferno_glDeleteProgram
extern _glDeleteShader _inferno_glDeleteShader;
#define glDeleteShader _inferno_glDeleteShader
extern _glDetachShader _inferno_glDetachShader;
#define glDetachShader _inferno_glDetachShader
extern _glDisableVertexAttribArray _inferno_glDisableVerglCreateShadertribArray;
#define glDisableVertexAttribArray _inferno_glDisableVerglCreateShadertribArray
extern _glEnableVertexAttribArray _inferno_glEnableVertexAttribArray;
#define glEnableVertexAttribArray _inferno_glEnableVertexAttribArray
extern _glGetActiveAttrib _inferno_glGetActiveAttrib;
#define glGetActiveAttrib _inferno_glGetActiveAttrib
extern _glGetActiveUniform _inferno_glGetActiveUniform;
#define glGetActiveUniform _inferno_glGetActiveUniform
extern _glGetAttachedShaders _inferno_glGetAttachedShaders;
#define glGetAttachedShaders _inferno_glGetAttachedShaders
extern _glGetAttribLocation _inferno_glGetAttribLocation;
#define glGetAttribLocation _inferno_glGetAttribLocation
extern _glGetProgramiv _inferno_glGetProgramiv;
#define glGetProgramiv _inferno_glGetProgramiv
extern _glGetProgramInfoLog _inferno_glGetProgramInfoLog;
#define glGetProgramInfoLog _inferno_glGetProgramInfoLog
extern _glGetShaderiv _inferno_glGetShaderiv;
#define glGetShaderiv _inferno_glGetShaderiv
extern _glGetShaderInfoLog _inferno_glGetShaderInfoLog;
#define glGetShaderInfoLog _inferno_glGetShaderInfoLog
extern _glGetShaderSource _inferno_glGetShaderSource;
#define glGetShaderSource _inferno_glGetShaderSource
extern _glGetUniformLocation _inferno_glGetUniformLocation;
#define glGetUniformLocation _inferno_glGetUniformLocation
extern _glGetUniformfv _inferno_glGetUniformfv;
#define glGetUniformfv _inferno_glGetUniformfv
extern _glGetUniformiv _inferno_glGetUniformiv;
#define glGetUniformiv _inferno_glGetUniformiv
extern _glGetVertexAttribdv _inferno_glGetVertexAttribdv;
#define glGetVertexAttribdv _inferno_glGetVertexAttribdv
extern _glGetVertexAttribfv _inferno_glGetVertexAttribfv;
#define glGetVertexAttribfv _inferno_glGetVertexAttribfv
extern _glGetVertexAttribiv _inferno_glGetVertexAttribiv;
#define glGetVertexAttribiv _inferno_glGetVertexAttribiv
extern _glGetVertexAttribPointerv _inferno_glGetVertexAttribPointerv;
#define glGetVertexAttribPointerv _inferno_glGetVertexAttribPointerv
extern _glIsProgram _inferno_glIsProgram;
#define glIsProgram _inferno_glIsProgram
extern _glIsShader _inferno_glIsShader;
#define glIsShader _inferno_glIsShader
extern _glLinkProgram _inferno_glLinkProgram;
#define glLinkProgram _inferno_glLinkProgram
extern _glShaderSource _inferno_glShaderSource;
#define glShaderSource _inferno_glShaderSource
extern _glUseProgram _inferno_glUseProgram;
#define glUseProgram _inferno_glUseProgram
extern _glUniform1f _inferno_glUniform1f;
#define glUniform1f _inferno_glUniform1f
extern _glUniform2f _inferno_glUniform2f;
#define glUniform2f _inferno_glUniform2f
extern _glUniform3f _inferno_glUniform3f;
#define glUniform3f _inferno_glUniform3f
extern _glUniform4f _inferno_glUniform4f;
#define glUniform4f _inferno_glUniform4f
extern _glUniform1i _inferno_glUniform1i;
#define glUniform1i _inferno_glUniform1i
extern _glUniform2i _inferno_glUniform2i;
#define glUniform2i _inferno_glUniform2i
extern _glUniform3i _inferno_glUniform3i;
#define glUniform3i _inferno_glUniform3i
extern _glUniform4i _inferno_glUniform4i;
#define glUniform4i _inferno_glUniform4i
extern _glUniform1fv _inferno_glUniform1fv;
#define glUniform1fv _inferno_glUniform1fv
extern _glUniform2fv _inferno_glUniform2fv;
#define glUniform2fv _inferno_glUniform2fv
extern _glUniform3fv _inferno_glUniform3fv;
#define glUniform3fv _inferno_glUniform3fv
extern _glUniform4fv _inferno_glUniform4fv;
#define glUniform4fv _inferno_glUniform4fv
extern _glUniform1iv _inferno_glUniform1iv;
#define glUniform1iv _inferno_glUniform1iv
extern _glUniform2iv _inferno_glUniform2iv;
#define glUniform2iv _inferno_glUniform2iv
extern _glUniform3iv _inferno_glUniform3iv;
#define glUniform3iv _inferno_glUniform3iv
extern _glUniform4iv _inferno_glUniform4iv;
#define glUniform4iv _inferno_glUniform4iv
extern _glUniformMatrix2fv _inferno_glUniformMatrix2fv;
#define glUniformMatrix2fv _inferno_glUniformMatrix2fv
extern _glUniformMatrix3fv _inferno_glUniformMatrix3fv;
#define glUniformMatrix3fv _inferno_glUniformMatrix3fv
extern _glUniformMatrix4fv _inferno_glUniformMatrix4fv;
#define glUniformMatrix4fv _inferno_glUniformMatrix4fv
extern _glValidateProgram _inferno_glValidateProgram;
#define glValidateProgram _inferno_glValidateProgram
extern _glVertexAttrib1d _inferno_glVertexAttrib1d;
#define glVertexAttrib1d _inferno_glVertexAttrib1d
extern _glVertexAttrib1dv _inferno_glVertexAttrib1dv;
#define glVertexAttrib1dv _inferno_glVertexAttrib1dv
extern _glVertexAttrib1f _inferno_glVertexAttrib1f;
#define glVertexAttrib1f _inferno_glVertexAttrib1f
extern _glVertexAttrib1fv _inferno_glVertexAttrib1fv;
#define glVertexAttrib1fv _inferno_glVertexAttrib1fv
extern _glVertexAttrib1s _inferno_glVertexAttrib1s;
#define glVertexAttrib1s _inferno_glVertexAttrib1s
extern _glVertexAttrib1sv _inferno_glVertexAttrib1sv;
#define glVertexAttrib1sv _inferno_glVertexAttrib1sv
extern _glVertexAttrib2d _inferno_glVertexAttrib2d;
#define glVertexAttrib2d _inferno_glVertexAttrib2d
extern _glVertexAttrib2dv _inferno_glVertexAttrib2dv;
#define glVertexAttrib2dv _inferno_glVertexAttrib2dv
extern _glVertexAttrib2f _inferno_glVertexAttrib2f;
#define glVertexAttrib2f _inferno_glVertexAttrib2f
extern _glVertexAttrib2fv _inferno_glVertexAttrib2fv;
#define glVertexAttrib2fv _inferno_glVertexAttrib2fv
extern _glVertexAttrib2s _inferno_glVertexAttrib2s;
#define glVertexAttrib2s _inferno_glVertexAttrib2s
extern _glVertexAttrib2sv _inferno_glVertexAttrib2sv;
#define glVertexAttrib2sv _inferno_glVertexAttrib2sv
extern _glVertexAttrib3d _inferno_glVertexAttrib3d;
#define glVertexAttrib3d _inferno_glVertexAttrib3d
extern _glVertexAttrib3dv _inferno_glVertexAttrib3dv;
#define glVertexAttrib3dv _inferno_glVertexAttrib3dv
extern _glVertexAttrib3f _inferno_glVertexAttrib3f;
#define glVertexAttrib3f _inferno_glVertexAttrib3f
extern _glVertexAttrib3fv _inferno_glVertexAttrib3fv;
#define glVertexAttrib3fv _inferno_glVertexAttrib3fv
extern _glVertexAttrib3s _inferno_glVertexAttrib3s;
#define glVertexAttrib3s _inferno_glVertexAttrib3s
extern _glVertexAttrib3sv _inferno_glVertexAttrib3sv;
#define glVertexAttrib3sv _inferno_glVertexAttrib3sv
extern _glVertexAttrib4Nbv _inferno_glVertexAttrib4Nbv;
#define glVertexAttrib4Nbv _inferno_glVertexAttrib4Nbv
extern _glVertexAttrib4Niv _inferno_glVertexAttrib4Niv;
#define glVertexAttrib4Niv _inferno_glVertexAttrib4Niv
extern _glVertexAttrib4Nsv _inferno_glVertexAttrib4Nsv;
#define glVertexAttrib4Nsv _inferno_glVertexAttrib4Nsv
extern _glVertexAttrib4Nub _inferno_glVertexAttrib4Nub;
#define glVertexAttrib4Nub _inferno_glVertexAttrib4Nub
extern _glVertexAttrib4Nubv _inferno_glVertexAttrib4Nubv;
#define glVertexAttrib4Nubv _inferno_glVertexAttrib4Nubv
extern _glVertexAttrib4Nuiv _inferno_glVertexAttrib4Nuiv;
#define glVertexAttrib4Nuiv _inferno_glVertexAttrib4Nuiv
extern _glVertexAttrib4Nusv _inferno_glVertexAttrib4Nusv;
#define glVertexAttrib4Nusv _inferno_glVertexAttrib4Nusv
extern _glVertexAttrib4bv _inferno_glVertexAttrib4bv;
#define glVertexAttrib4bv _inferno_glVertexAttrib4bv
extern _glVertexAttrib4d _inferno_glVertexAttrib4d;
#define glVertexAttrib4d _inferno_glVertexAttrib4d
extern _glVertexAttrib4dv _inferno_glVertexAttrib4dv;
#define glVertexAttrib4dv _inferno_glVertexAttrib4dv
extern _glVertexAttrib4f _inferno_glVertexAttrib4f;
#define glVertexAttrib4f _inferno_glVertexAttrib4f
extern _glVertexAttrib4fv _inferno_glVertexAttrib4fv;
#define glVertexAttrib4fv _inferno_glVertexAttrib4fv
extern _glVertexAttrib4iv _inferno_glVertexAttrib4iv;
#define glVertexAttrib4iv _inferno_glVertexAttrib4iv
extern _glVertexAttrib4s _inferno_glVertexAttrib4s;
#define glVertexAttrib4s _inferno_glVertexAttrib4s
extern _glVertexAttrib4sv _inferno_glVertexAttrib4sv;
#define glVertexAttrib4sv _inferno_glVertexAttrib4sv
extern _glVertexAttrib4ubv _inferno_glVertexAttrib4ubv;
#define glVertexAttrib4ubv _inferno_glVertexAttrib4ubv
extern _glVertexAttrib4uiv _inferno_glVertexAttrib4uiv;
#define glVertexAttrib4uiv _inferno_glVertexAttrib4uiv
extern _glVertexAttrib4usv _inferno_glVertexAttrib4usv;
#define glVertexAttrib4usv _inferno_glVertexAttrib4usv
extern _glVertexAttribPointer _inferno_glVertexAttribPointer;
#define glVertexAttribPointer _inferno_glVertexAttribPointer

extern _glClearBufferData _inferno_glClearBufferData;
#define glClearBufferData _inferno_glClearBufferData
extern _glClearBufferSubData _inferno_glClearBufferSubData;
#define glClearBufferSubData _inferno_glClearBufferSubData
extern _glDispatchCompute _inferno_glDispatchCompute;
#define glDispatchCompute _inferno_glDispatchCompute
extern _glDispatchComputeIndirect _inferno_glDispatchComputeIndirect;
#define glDispatchComputeIndirect _inferno_glDispatchComputeIndirect
extern _glCopyImageSubData _inferno_glCopyImageSubData;
#define glCopyImageSubData _inferno_glCopyImageSubData
extern _glFramebufferParameteri _inferno_glFramebufferParameteri;
#define glFramebufferParameteri _inferno_glFramebufferParameteri
extern _glGetFramebufferParameteriv _inferno_glGetFramebufferParameteriv;
#define glGetFramebufferParameteriv _inferno_glGetFramebufferParameteriv
extern _glGetInternalformati64v _inferno_glGetInternalformati64v;
#define glGetInternalformati64v _inferno_glGetInternalformati64v
extern _glInvalidateTexSubImage _inferno_glInvalidateTexSubImage;
#define glInvalidateTexSubImage _inferno_glInvalidateTexSubImage
extern _glInvalidateTexImage _inferno_glInvalidateTexImage;
#define glInvalidateTexImage _inferno_glInvalidateTexImage
extern _glInvalidateBufferSubData _inferno_glInvalidateBufferSubData;
#define glInvalidateBufferSubData _inferno_glInvalidateBufferSubData
extern _glInvalidateBufferData _inferno_glInvalidateBufferData;
#define glInvalidateBufferData _inferno_glInvalidateBufferData
extern _glInvalidateFramebuffer _inferno_glInvalidateFramebuffer;
#define glInvalidateFramebuffer _inferno_glInvalidateFramebuffer
extern _glInvalidateSubFramebuffer _inferno_glInvalidateSubFramebuffer;
#define glInvalidateSubFramebuffer _inferno_glInvalidateSubFramebuffer
extern _glMultiDrawArraysIndirect _inferno_glMultiDrawArraysIndirect;
#define glMultiDrawArraysIndirect _inferno_glMultiDrawArraysIndirect
extern _glMultiDrawElementsIndirect _inferno_glMultiDrawElementsIndirect;
#define glMultiDrawElementsIndirect _inferno_glMultiDrawElementsIndirect
extern _glGetProgramInterfaceiv _inferno_glGetProgramInterfaceiv;
#define glGetProgramInterfaceiv _inferno_glGetProgramInterfaceiv
extern _glGetProgramResourceIndex _inferno_glGetProgramResourceIndex;
#define glGetProgramResourceIndex _inferno_glGetProgramResourceIndex
extern _glGetProgramResourceName _inferno_glGetProgramResourceName;
#define glGetProgramResourceName _inferno_glGetProgramResourceName
extern _glGetProgramResourceiv _inferno_glGetProgramResourceiv;
#define glGetProgramResourceiv _inferno_glGetProgramResourceiv
extern _glGetProgramResourceLocation _inferno_glGetProgramResourceLocation;
#define glGetProgramResourceLocation _inferno_glGetProgramResourceLocation
extern _glGetProgramResourceLocationIndex _inferno_glGetProgramResourceLocationIndex;
#define glGetProgramResourceLocationIndex _inferno_glGetProgramResourceLocationIndex
extern _glShaderStorageBlockBinding _inferno_glShaderStorageBlockBinding;
#define glShaderStorageBlockBinding _inferno_glShaderStorageBlockBinding
extern _glTexBufferRange _inferno_glTexBufferRange;
#define glTexBufferRange _inferno_glTexBufferRange
extern _glTexStorage2DMultisample _inferno_glTexStorage2DMultisample;
#define glTexStorage2DMultisample _inferno_glTexStorage2DMultisample
extern _glTexStorage3DMultisample _inferno_glTexStorage3DMultisample;
#define glTexStorage3DMultisample _inferno_glTexStorage3DMultisample
extern _glTextureView _inferno_glTextureView;
#define glTextureView _inferno_glTextureView
extern _glVertexAttribFormat _inferno_glVertexAttribFormat;
#define glVertexAttribFormat _inferno_glVertexAttribFormat
extern _glVertexAttribIFormat _inferno_glVertexAttribIFormat;
#define glVertexAttribIFormat _inferno_glVertexAttribIFormat
extern _glVertexAttribLFormat _inferno_glVertexAttribLFormat;
#define glVertexAttribLFormat _inferno_glVertexAttribLFormat
extern _glVertexAttribBinding _inferno_glVertexAttribBinding;
#define glVertexAttribBinding _inferno_glVertexAttribBinding
extern _glVertexBindingDivisor _inferno_glVertexBindingDivisor;
#define glVertexBindingDivisor _inferno_glVertexBindingDivisor
extern _glDebugMessageControl _inferno_glDebugMessageControl;
#define glDebugMessageControl _inferno_glDebugMessageControl
extern _glDebugMessageInsert _inferno_glDebugMessageInsert;
#define glDebugMessageInsert _inferno_glDebugMessageInsert
extern _glDebugMessageCallback _inferno_glDebugMessageCallback;
#define glDebugMessageCallback _inferno_glDebugMessageCallback
extern _glGetDebugMessageLog _inferno_glGetDebugMessageLog;
#define glGetDebugMessageLog _inferno_glGetDebugMessageLog
extern _glPushDebugGroup _inferno_glPushDebugGroup;
#define glPushDebugGroup _inferno_glPushDebugGroup
extern _glPopDebugGroup _inferno_glPopDebugGroup;
#define glPopDebugGroup _inferno_glPopDebugGroup
extern _glObjectLabel _inferno_glObjectLabel;
#define glObjectLabel _inferno_glObjectLabel
extern _glGetObjectLabel _inferno_glGetObjectLabel;
#define glGetObjectLabel _inferno_glGetObjectLabel
extern _glObjectPtrLabel _inferno_glObjectPtrLabel;
#define glObjectPtrLabel _inferno_glObjectPtrLabel
extern _glGetObjectPtrLabel _inferno_glGetObjectPtrLabel;
#define glGetObjectPtrLabel _inferno_glGetObjectPtrLabel
extern _glBindVertexBuffer _inferno_glBindVertexBuffer;
#define glBindVertexBuffer _inferno_glBindVertexBuffer
extern _glUnmapNamedBuffer _inferno_glUnmapNamedBuffer;
#define glUnmapNamedBuffer _inferno_glUnmapNamedBuffer
extern _glClipControl _inferno_glClipControl;
#define glClipControl _inferno_glClipControl
extern _glCreateTransformFeedbacks _inferno_glCreateTransformFeedbacks;
#define glCreateTransformFeedbacks _inferno_glCreateTransformFeedbacks
extern _glTransformFeedbackBufferBase _inferno_glTransformFeedbackBufferBase;
#define glTransformFeedbackBufferBase _inferno_glTransformFeedbackBufferBase
extern _glTransformFeedbackBufferRange _inferno_glTransformFeedbackBufferRange;
#define glTransformFeedbackBufferRange _inferno_glTransformFeedbackBufferRange
extern _glGetTransformFeedbackiv _inferno_glGetTransformFeedbackiv;
#define glGetTransformFeedbackiv _inferno_glGetTransformFeedbackiv
extern _glGetTransformFeedbacki_v _inferno_glGetTransformFeedbacki_v;
#define glGetTransformFeedbacki_v _inferno_glGetTransformFeedbacki_v
extern _glGetTransformFeedbacki64_v _inferno_glGetTransformFeedbacki64_v;
#define glGetTransformFeedbacki64_v _inferno_glGetTransformFeedbacki64_v
extern _glCreateBuffers _inferno_glCreateBuffers;
#define glCreateBuffers _inferno_glCreateBuffers
extern _glNamedBufferStorage _inferno_glNamedBufferStorage;
#define glNamedBufferStorage _inferno_glNamedBufferStorage
extern _glNamedBufferData _inferno_glNamedBufferData;
#define glNamedBufferData _inferno_glNamedBufferData
extern _glNamedBufferSubData _inferno_glNamedBufferSubData;
#define glNamedBufferSubData _inferno_glNamedBufferSubData
extern _glCopyNamedBufferSubData _inferno_glCopyNamedBufferSubData;
#define glCopyNamedBufferSubData _inferno_glCopyNamedBufferSubData
extern _glClearNamedBufferData _inferno_glClearNamedBufferData;
#define glClearNamedBufferData _inferno_glClearNamedBufferData
extern _glClearNamedBufferSubData _inferno_glClearNamedBufferSubData;
#define glClearNamedBufferSubData _inferno_glClearNamedBufferSubData
extern _glFlushMappedNamedBufferRange _inferno_glFlushMappedNamedBufferRange;
#define glFlushMappedNamedBufferRange _inferno_glFlushMappedNamedBufferRange
extern _glGetNamedBufferParameteriv _inferno_glGetNamedBufferParameteriv;
#define glGetNamedBufferParameteriv _inferno_glGetNamedBufferParameteriv
extern _glGetNamedBufferParameteri64v _inferno_glGetNamedBufferParameteri64v;
#define glGetNamedBufferParameteri64v _inferno_glGetNamedBufferParameteri64v
extern _glGetNamedBufferPointerv _inferno_glGetNamedBufferPointerv;
#define glGetNamedBufferPointerv _inferno_glGetNamedBufferPointerv
extern _glGetNamedBufferSubData _inferno_glGetNamedBufferSubData;
#define glGetNamedBufferSubData _inferno_glGetNamedBufferSubData
extern _glCreateFramebuffers _inferno_glCreateFramebuffers;
#define glCreateFramebuffers _inferno_glCreateFramebuffers
extern _glNamedFramebufferRenderbuffer _inferno_glNamedFramebufferRenderbuffer;
#define glNamedFramebufferRenderbuffer _inferno_glNamedFramebufferRenderbuffer
extern _glNamedFramebufferParameteri _inferno_glNamedFramebufferParameteri;
#define glNamedFramebufferParameteri _inferno_glNamedFramebufferParameteri
extern _glNamedFramebufferTexture _inferno_glNamedFramebufferTexture;
#define glNamedFramebufferTexture _inferno_glNamedFramebufferTexture
extern _glNamedFramebufferTextureLayer _inferno_glNamedFramebufferTextureLayer;
#define glNamedFramebufferTextureLayer _inferno_glNamedFramebufferTextureLayer
extern _glNamedFramebufferDrawBuffer _inferno_glNamedFramebufferDrawBuffer;
#define glNamedFramebufferDrawBuffer _inferno_glNamedFramebufferDrawBuffer
extern _glNamedFramebufferDrawBuffers _inferno_glNamedFramebufferDrawBuffers;
#define glNamedFramebufferDrawBuffers _inferno_glNamedFramebufferDrawBuffers
extern _glNamedFramebufferReadBuffer _inferno_glNamedFramebufferReadBuffer;
#define glNamedFramebufferReadBuffer _inferno_glNamedFramebufferReadBuffer
extern _glInvalidateNamedFramebufferData _inferno_glInvalidateNamedFramebufferData;
#define glInvalidateNamedFramebufferData _inferno_glInvalidateNamedFramebufferData
extern _glInvalidateNamedFramebufferSubData _inferno_glInvalidateNamedFramebufferSubData;
#define glInvalidateNamedFramebufferSubData _inferno_glInvalidateNamedFramebufferSubData
extern _glClearNamedFramebufferiv _inferno_glClearNamedFramebufferiv;
#define glClearNamedFramebufferiv _inferno_glClearNamedFramebufferiv
extern _glClearNamedFramebufferuiv _inferno_glClearNamedFramebufferuiv;
#define glClearNamedFramebufferuiv _inferno_glClearNamedFramebufferuiv
extern _glClearNamedFramebufferfv _inferno_glClearNamedFramebufferfv;
#define glClearNamedFramebufferfv _inferno_glClearNamedFramebufferfv
extern _glClearNamedFramebufferfi _inferno_glClearNamedFramebufferfi;
#define glClearNamedFramebufferfi _inferno_glClearNamedFramebufferfi
extern _glBlitNamedFramebuffer _inferno_glBlitNamedFramebuffer;
#define glBlitNamedFramebuffer _inferno_glBlitNamedFramebuffer
extern _glCheckNamedFramebufferStatus _inferno_glCheckNamedFramebufferStatus;
#define glCheckNamedFramebufferStatus _inferno_glCheckNamedFramebufferStatus
extern _glGetNamedFramebufferParameteriv _inferno_glGetNamedFramebufferParameteriv;
#define glGetNamedFramebufferParameteriv _inferno_glGetNamedFramebufferParameteriv
extern _glGetNamedFramebufferAttachmentParameteriv _inferno_glGetNamedFramebufferAttachmentParameteriv;
#define glGetNamedFramebufferAttachmentParameteriv _inferno_glGetNamedFramebufferAttachmentParameteriv
extern _glCreateRenderbuffers _inferno_glCreateRenderbuffers;
#define glCreateRenderbuffers _inferno_glCreateRenderbuffers
extern _glNamedRenderbufferStorage _inferno_glNamedRenderbufferStorage;
#define glNamedRenderbufferStorage _inferno_glNamedRenderbufferStorage
extern _glNamedRenderbufferStorageMultisample _inferno_glNamedRenderbufferStorageMultisample;
#define glNamedRenderbufferStorageMultisample _inferno_glNamedRenderbufferStorageMultisample
extern _glGetNamedRenderbufferParameteriv _inferno_glGetNamedRenderbufferParameteriv;
#define glGetNamedRenderbufferParameteriv _inferno_glGetNamedRenderbufferParameteriv
extern _glCreateTextures _inferno_glCreateTextures;
#define glCreateTextures _inferno_glCreateTextures
extern _glTextureBuffer _inferno_glTextureBuffer;
#define glTextureBuffer _inferno_glTextureBuffer
extern _glTextureBufferRange _inferno_glTextureBufferRange;
#define glTextureBufferRange _inferno_glTextureBufferRange
extern _glTextureStorage1D _inferno_glTextureStorage1D;
#define glTextureStorage1D _inferno_glTextureStorage1D
extern _glTextureStorage2D _inferno_glTextureStorage2D;
#define glTextureStorage2D _inferno_glTextureStorage2D
extern _glTextureStorage3D _inferno_glTextureStorage3D;
#define glTextureStorage3D _inferno_glTextureStorage3D
extern _glTextureStorage2DMultisample _inferno_glTextureStorage2DMultisample;
#define glTextureStorage2DMultisample _inferno_glTextureStorage2DMultisample
extern _glTextureStorage3DMultisample _inferno_glTextureStorage3DMultisample;
#define glTextureStorage3DMultisample _inferno_glTextureStorage3DMultisample
extern _glTextureSubImage1D _inferno_glTextureSubImage1D;
#define glTextureSubImage1D _inferno_glTextureSubImage1D
extern _glTextureSubImage2D _inferno_glTextureSubImage2D;
#define glTextureSubImage2D _inferno_glTextureSubImage2D
extern _glTextureSubImage3D _inferno_glTextureSubImage3D;
#define glTextureSubImage3D _inferno_glTextureSubImage3D
extern _glCompressedTextureSubImage1D _inferno_glCompressedTextureSubImage1D;
#define glCompressedTextureSubImage1D _inferno_glCompressedTextureSubImage1D
extern _glCompressedTextureSubImage2D _inferno_glCompressedTextureSubImage2D;
#define glCompressedTextureSubImage2D _inferno_glCompressedTextureSubImage2D
extern _glCompressedTextureSubImage3D _inferno_glCompressedTextureSubImage3D;
#define glCompressedTextureSubImage3D _inferno_glCompressedTextureSubImage3D
extern _glCopyTextureSubImage1D _inferno_glCopyTextureSubImage1D;
#define glCopyTextureSubImage1D _inferno_glCopyTextureSubImage1D
extern _glCopyTextureSubImage2D _inferno_glCopyTextureSubImage2D;
#define glCopyTextureSubImage2D _inferno_glCopyTextureSubImage2D
extern _glCopyTextureSubImage3D _inferno_glCopyTextureSubImage3D;
#define glCopyTextureSubImage3D _inferno_glCopyTextureSubImage3D
extern _glTextureParameterf _inferno_glTextureParameterf;
#define glTextureParameterf _inferno_glTextureParameterf
extern _glTextureParameterfv _inferno_glTextureParameterfv;
#define glTextureParameterfv _inferno_glTextureParameterfv
extern _glTextureParameteri _inferno_glTextureParameteri;
#define glTextureParameteri _inferno_glTextureParameteri
extern _glTextureParameterIiv _inferno_glTextureParameterIiv;
#define glTextureParameterIiv _inferno_glTextureParameterIiv
extern _glTextureParameterIuiv _inferno_glTextureParameterIuiv;
#define glTextureParameterIuiv _inferno_glTextureParameterIuiv
extern _glTextureParameteriv _inferno_glTextureParameteriv;
#define glTextureParameteriv _inferno_glTextureParameteriv
extern _glGenerateTextureMipmap _inferno_glGenerateTextureMipmap;
#define glGenerateTextureMipmap _inferno_glGenerateTextureMipmap
extern _glBindTextureUnit _inferno_glBindTextureUnit;
#define glBindTextureUnit _inferno_glBindTextureUnit
extern _glGetTextureImage _inferno_glGetTextureImage;
#define glGetTextureImage _inferno_glGetTextureImage
extern _glGetCompressedTextureImage _inferno_glGetCompressedTextureImage;
#define glGetCompressedTextureImage _inferno_glGetCompressedTextureImage
extern _glGetTextureLevelParameterfv _inferno_glGetTextureLevelParameterfv;
#define glGetTextureLevelParameterfv _inferno_glGetTextureLevelParameterfv
extern _glGetTextureLevelParameteriv _inferno_glGetTextureLevelParameteriv;
#define glGetTextureLevelParameteriv _inferno_glGetTextureLevelParameteriv
extern _glGetTextureParameterfv _inferno_glGetTextureParameterfv;
#define glGetTextureParameterfv _inferno_glGetTextureParameterfv
extern _glGetTextureParameterIiv _inferno_glGetTextureParameterIiv;
#define glGetTextureParameterIiv _inferno_glGetTextureParameterIiv
extern _glGetTextureParameterIuiv _inferno_glGetTextureParameterIuiv;
#define glGetTextureParameterIuiv _inferno_glGetTextureParameterIuiv
extern _glGetTextureParameteriv _inferno_glGetTextureParameteriv;
#define glGetTextureParameteriv _inferno_glGetTextureParameteriv
extern _glCreateVertexArrays _inferno_glCreateVertexArrays;
#define glCreateVertexArrays _inferno_glCreateVertexArrays
extern _glDisableVertexArrayAttrib _inferno_glDisableVertexArrayAttrib;
#define glDisableVertexArrayAttrib _inferno_glDisableVertexArrayAttrib
extern _glEnableVertexArrayAttrib _inferno_glEnableVertexArrayAttrib;
#define glEnableVertexArrayAttrib _inferno_glEnableVertexArrayAttrib
extern _glVertexArrayElementBuffer _inferno_glVertexArrayElementBuffer;
#define glVertexArrayElementBuffer _inferno_glVertexArrayElementBuffer
extern _glVertexArrayVertexBuffer _inferno_glVertexArrayVertexBuffer;
#define glVertexArrayVertexBuffer _inferno_glVertexArrayVertexBuffer
extern _glVertexArrayVertexBuffers _inferno_glVertexArrayVertexBuffers;
#define glVertexArrayVertexBuffers _inferno_glVertexArrayVertexBuffers
extern _glVertexArrayAttribBinding _inferno_glVertexArrayAttribBinding;
#define glVertexArrayAttribBinding _inferno_glVertexArrayAttribBinding
extern _glVertexArrayAttribFormat _inferno_glVertexArrayAttribFormat;
#define glVertexArrayAttribFormat _inferno_glVertexArrayAttribFormat
extern _glVertexArrayAttribIFormat _inferno_glVertexArrayAttribIFormat;
#define glVertexArrayAttribIFormat _inferno_glVertexArrayAttribIFormat
extern _glVertexArrayAttribLFormat _inferno_glVertexArrayAttribLFormat;
#define glVertexArrayAttribLFormat _inferno_glVertexArrayAttribLFormat
extern _glVertexArrayBindingDivisor _inferno_glVertexArrayBindingDivisor;
#define glVertexArrayBindingDivisor _inferno_glVertexArrayBindingDivisor
extern _glGetVertexArrayiv _inferno_glGetVertexArrayiv;
#define glGetVertexArrayiv _inferno_glGetVertexArrayiv
extern _glGetVertexArrayIndexediv _inferno_glGetVertexArrayIndexediv;
#define glGetVertexArrayIndexediv _inferno_glGetVertexArrayIndexediv
extern _glGetVertexArrayIndexed64iv _inferno_glGetVertexArrayIndexed64iv;
#define glGetVertexArrayIndexed64iv _inferno_glGetVertexArrayIndexed64iv
extern _glCreateSamplers _inferno_glCreateSamplers;
#define glCreateSamplers _inferno_glCreateSamplers
extern _glCreateProgramPipelines _inferno_glCreateProgramPipelines;
#define glCreateProgramPipelines _inferno_glCreateProgramPipelines
extern _glCreateQueries _inferno_glCreateQueries;
#define glCreateQueries _inferno_glCreateQueries
extern _glGetQueryBufferObjecti64v _inferno_glGetQueryBufferObjecti64v;
#define glGetQueryBufferObjecti64v _inferno_glGetQueryBufferObjecti64v
extern _glGetQueryBufferObjectiv _inferno_glGetQueryBufferObjectiv;
#define glGetQueryBufferObjectiv _inferno_glGetQueryBufferObjectiv
extern _glGetQueryBufferObjectui64v _inferno_glGetQueryBufferObjectui64v;
#define glGetQueryBufferObjectui64v _inferno_glGetQueryBufferObjectui64v
extern _glGetQueryBufferObjectuiv _inferno_glGetQueryBufferObjectuiv;
#define glGetQueryBufferObjectuiv _inferno_glGetQueryBufferObjectuiv
extern _glMemoryBarrierByRegion _inferno_glMemoryBarrierByRegion;
#define glMemoryBarrierByRegion _inferno_glMemoryBarrierByRegion
extern _glGetTextureSubImage _inferno_glGetTextureSubImage;
#define glGetTextureSubImage _inferno_glGetTextureSubImage
extern _glGetCompressedTextureSubImage _inferno_glGetCompressedTextureSubImage;
#define glGetCompressedTextureSubImage _inferno_glGetCompressedTextureSubImage
extern _glGetGraphicsResetStatus _inferno_glGetGraphicsResetStatus;
#define glGetGraphicsResetStatus _inferno_glGetGraphicsResetStatus
extern _glGetnCompressedTexImage _inferno_glGetnCompressedTexImage;
#define glGetnCompressedTexImage _inferno_glGetnCompressedTexImage
extern _glGetnTexImage _inferno_glGetnTexImage;
#define glGetnTexImage _inferno_glGetnTexImage
extern _glGetnUniformdv _inferno_glGetnUniformdv;
#define glGetnUniformdv _inferno_glGetnUniformdv
extern _glGetnUniformfv _inferno_glGetnUniformfv;
#define glGetnUniformfv _inferno_glGetnUniformfv
extern _glGetnUniformiv _inferno_glGetnUniformiv;
#define glGetnUniformiv _inferno_glGetnUniformiv
extern _glGetnUniformuiv _inferno_glGetnUniformuiv;
#define glGetnUniformuiv _inferno_glGetnUniformuiv
extern _glReadnPixels _inferno_glReadnPixels;
#define glReadnPixels _inferno_glReadnPixels
extern _glTextureBarrier _inferno_glTextureBarrier;
#define glTextureBarrier _inferno_glTextureBarrier

extern _glColorMaski _inferno_glColorMaski;
#define glColorMaski _inferno_glColorMaski
extern _glGetBooleani_v _inferno_glGetBooleani_v;
#define glGetBooleani_v _inferno_glGetBooleani_v
extern _glGetIntegeri_v _inferno_glGetIntegeri_v;
#define glGetIntegeri_v _inferno_glGetIntegeri_v
extern _glEnablei _inferno_glEnablei;
#define glEnablei _inferno_glEnablei
extern _glDisablei _inferno_glDisablei;
#define glDisablei _inferno_glDisablei
extern _glIsEnabledi _inferno_glIsEnabledi;
#define glIsEnabledi _inferno_glIsEnabledi
extern _glBeginTransformFeedback _inferno_glBeginTransformFeedback;
#define glBeginTransformFeedback _inferno_glBeginTransformFeedback
extern _glEndTransformFeedback _inferno_glEndTransformFeedback;
#define glEndTransformFeedback _inferno_glEndTransformFeedback
extern _glBindBufferRange _inferno_glBindBufferRange;
#define glBindBufferRange _inferno_glBindBufferRange
extern _glBindBufferBase _inferno_glBindBufferBase;
#define glBindBufferBase _inferno_glBindBufferBase
extern _glTransformFeedbackVaryings _inferno_glTransformFeedbackVaryings;
#define glTransformFeedbackVaryings _inferno_glTransformFeedbackVaryings
extern _glGetTransformFeedbackVarying _inferno_glGetTransformFeedbackVarying;
#define glGetTransformFeedbackVarying _inferno_glGetTransformFeedbackVarying
extern _glClampColor _inferno_glClampColor;
#define glClampColor _inferno_glClampColor
extern _glBeginConditionalRender _inferno_glBeginConditionalRender;
#define glBeginConditionalRender _inferno_glBeginConditionalRender
extern _glEndConditionalRender _inferno_glEndConditionalRender;
#define glEndConditionalRender _inferno_glEndConditionalRender
extern _glVertexAttribIPointer _inferno_glVertexAttribIPointer;
#define glVertexAttribIPointer _inferno_glVertexAttribIPointer
extern _glGetVertexAttribIiv _inferno_glGetVertexAttribIiv;
#define glGetVertexAttribIiv _inferno_glGetVertexAttribIiv
extern _glGetVertexAttribIuiv _inferno_glGetVertexAttribIuiv;
#define glGetVertexAttribIuiv _inferno_glGetVertexAttribIuiv
extern _glVertexAttribI1i _inferno_glVertexAttribI1i;
#define glVertexAttribI1i _inferno_glVertexAttribI1i
extern _glVertexAttribI2i _inferno_glVertexAttribI2i;
#define glVertexAttribI2i _inferno_glVertexAttribI2i
extern _glVertexAttribI3i _inferno_glVertexAttribI3i;
#define glVertexAttribI3i _inferno_glVertexAttribI3i
extern _glVertexAttribI4i _inferno_glVertexAttribI4i;
#define glVertexAttribI4i _inferno_glVertexAttribI4i
extern _glVertexAttribI1ui _inferno_glVertexAttribI1ui;
#define glVertexAttribI1ui _inferno_glVertexAttribI1ui
extern _glVertexAttribI2ui _inferno_glVertexAttribI2ui;
#define glVertexAttribI2ui _inferno_glVertexAttribI2ui
extern _glVertexAttribI3ui _inferno_glVertexAttribI3ui;
#define glVertexAttribI3ui _inferno_glVertexAttribI3ui
extern _glVertexAttribI4ui _inferno_glVertexAttribI4ui;
#define glVertexAttribI4ui _inferno_glVertexAttribI4ui
extern _glVertexAttribI1iv _inferno_glVertexAttribI1iv;
#define glVertexAttribI1iv _inferno_glVertexAttribI1iv
extern _glVertexAttribI2iv _inferno_glVertexAttribI2iv;
#define glVertexAttribI2iv _inferno_glVertexAttribI2iv
extern _glVertexAttribI3iv _inferno_glVertexAttribI3iv;
#define glVertexAttribI3iv _inferno_glVertexAttribI3iv
extern _glVertexAttribI4iv _inferno_glVertexAttribI4iv;
#define glVertexAttribI4iv _inferno_glVertexAttribI4iv
extern _glVertexAttribI1uiv _inferno_glVertexAttribI1uiv;
#define glVertexAttribI1uiv _inferno_glVertexAttribI1uiv
extern _glVertexAttribI2uiv _inferno_glVertexAttribI2uiv;
#define glVertexAttribI2uiv _inferno_glVertexAttribI2uiv
extern _glVertexAttribI3uiv _inferno_glVertexAttribI3uiv;
#define glVertexAttribI3uiv _inferno_glVertexAttribI3uiv
extern _glVertexAttribI4uiv _inferno_glVertexAttribI4uiv;
#define glVertexAttribI4uiv _inferno_glVertexAttribI4uiv
extern _glVertexAttribI4bv _inferno_glVertexAttribI4bv;
#define glVertexAttribI4bv _inferno_glVertexAttribI4bv
extern _glVertexAttribI4sv _inferno_glVertexAttribI4sv;
#define glVertexAttribI4sv _inferno_glVertexAttribI4sv
extern _glVertexAttribI4ubv _inferno_glVertexAttribI4ubv;
#define glVertexAttribI4ubv _inferno_glVertexAttribI4ubv
extern _glVertexAttribI4usv _inferno_glVertexAttribI4usv;
#define glVertexAttribI4usv _inferno_glVertexAttribI4usv
extern _glGetUniformuiv _inferno_glGetUniformuiv;
#define glGetUniformuiv _inferno_glGetUniformuiv
extern _glBindFragDataLocation _inferno_glBindFragDataLocation;
#define glBindFragDataLocation _inferno_glBindFragDataLocation
extern _glGetFragDataLocation _inferno_glGetFragDataLocation;
#define glGetFragDataLocation _inferno_glGetFragDataLocation
extern _glUniform1ui _inferno_glUniform1ui;
#define glUniform1ui _inferno_glUniform1ui
extern _glUniform2ui _inferno_glUniform2ui;
#define glUniform2ui _inferno_glUniform2ui
extern _glUniform3ui _inferno_glUniform3ui;
#define glUniform3ui _inferno_glUniform3ui
extern _glUniform4ui _inferno_glUniform4ui;
#define glUniform4ui _inferno_glUniform4ui
extern _glUniform1uiv _inferno_glUniform1uiv;
#define glUniform1uiv _inferno_glUniform1uiv
extern _glUniform2uiv _inferno_glUniform2uiv;
#define glUniform2uiv _inferno_glUniform2uiv
extern _glUniform3uiv _inferno_glUniform3uiv;
#define glUniform3uiv _inferno_glUniform3uiv
extern _glUniform4uiv _inferno_glUniform4uiv;
#define glUniform4uiv _inferno_glUniform4uiv
extern _glTexParameterIiv _inferno_glTexParameterIiv;
#define glTexParameterIiv _inferno_glTexParameterIiv
extern _glTexParameterIuiv _inferno_glTexParameterIuiv;
#define glTexParameterIuiv _inferno_glTexParameterIuiv
extern _glGetTexParameterIiv _inferno_glGetTexParameterIiv;
#define glGetTexParameterIiv _inferno_glGetTexParameterIiv
extern _glGetTexParameterIuiv _inferno_glGetTexParameterIuiv;
#define glGetTexParameterIuiv _inferno_glGetTexParameterIuiv
extern _glClearBufferiv _inferno_glClearBufferiv;
#define glClearBufferiv _inferno_glClearBufferiv
extern _glClearBufferuiv _inferno_glClearBufferuiv;
#define glClearBufferuiv _inferno_glClearBufferuiv
extern _glClearBufferfv _inferno_glClearBufferfv;
#define glClearBufferfv _inferno_glClearBufferfv
extern _glClearBufferfi _inferno_glClearBufferfi;
#define glClearBufferfi _inferno_glClearBufferfi

extern _glGetStringi _inferno__glGetStringi;
#define glGetStringi _inferno__glGetStringi
extern _glIsRenderbuffer _inferno__glIsRenderbuffer;
#define glIsRenderbuffer _inferno__glIsRenderbuffer
extern _glBindRenderbuffer _inferno__glBindRenderbuffer;
#define glBindRenderbuffer _inferno__glBindRenderbuffer
extern _glDeleteRenderbuffers _inferno__glDeleteRenderbuffers;
#define glDeleteRenderbuffers _inferno__glDeleteRenderbuffers
extern _glGenRenderbuffers _inferno__glGenRenderbuffers;
#define glGenRenderbuffers _inferno__glGenRenderbuffers
extern _glRenderbufferStorage _inferno__glRenderbufferStorage;
#define glRenderbufferStorage _inferno__glRenderbufferStorage
extern _glGetRenderbufferParameteriv _inferno__glGetRenderbufferParameteriv;
#define glGetRenderbufferParameteriv _inferno__glGetRenderbufferParameteriv
extern _glIsFramebuffer _inferno__glIsFramebuffer;
#define glIsFramebuffer _inferno__glIsFramebuffer
extern _glBindFramebuffer _inferno__glBindFramebuffer;
#define glBindFramebuffer _inferno__glBindFramebuffer
extern _glDeleteFramebuffers _inferno__glDeleteFramebuffers;
#define glDeleteFramebuffers _inferno__glDeleteFramebuffers
extern _glGenFramebuffers _inferno__glGenFramebuffers;
#define glGenFramebuffers _inferno__glGenFramebuffers
extern _glCheckFramebufferStatus _inferno__glCheckFramebufferStatus;
#define glCheckFramebufferStatus _inferno__glCheckFramebufferStatus
extern _glFramebufferTexture1D _inferno__glFramebufferTexture1D;
#define glFramebufferTexture1D _inferno__glFramebufferTexture1D
extern _glFramebufferTexture2D _inferno__glFramebufferTexture2D;
#define glFramebufferTexture2D _inferno__glFramebufferTexture2D
extern _glFramebufferTexture3D _inferno__glFramebufferTexture3D;
#define glFramebufferTexture3D _inferno__glFramebufferTexture3D
extern _glFramebufferRenderbuffer _inferno__glFramebufferRenderbuffer;
#define glFramebufferRenderbuffer _inferno__glFramebufferRenderbuffer
extern _glGetFramebufferAttachmentParameteriv _inferno__glGetFramebufferAttachmentParameteriv;
#define glGetFramebufferAttachmentParameteriv _inferno__glGetFramebufferAttachmentParameteriv
extern _glGenerateMipmap _inferno__glGenerateMipmap;
#define glGenerateMipmap _inferno__glGenerateMipmap
extern _glBlitFramebuffer _inferno__glBlitFramebuffer;
#define glBlitFramebuffer _inferno__glBlitFramebuffer
extern _glRenderbufferStorageMultisample _inferno__glRenderbufferStorageMultisample;
#define glRenderbufferStorageMultisample _inferno__glRenderbufferStorageMultisample
extern _glFramebufferTextureLayer _inferno__glFramebufferTextureLayer;
#define glFramebufferTextureLayer _inferno__glFramebufferTextureLayer

extern _glMapBufferRange _inferno_glMapBufferRange;
#define glMapBufferRange _inferno_glMapBufferRange
extern _glFlushMappedBufferRange _inferno_glFlushMappedBufferRange;
#define glFlushMappedBufferRange _inferno_glFlushMappedBufferRange
extern _glBindVertexArray _inferno_glBindVertexArray;
#define glBindVertexArray _inferno_glBindVertexArray
extern _glDeleteVertexArrays _inferno_glDeleteVertexArrays;
#define glDeleteVertexArrays _inferno_glDeleteVertexArrays
extern _glGenVertexArrays _inferno_glGenVertexArrays;
#define glGenVertexArrays _inferno_glGenVertexArrays
extern _glIsVertexArray _inferno_glIsVertexArray;
#define glIsVertexArray _inferno_glIsVertexArray

static inline void* getProcAddress(const char* name){
    void* result = (void*)glXGetProcAddress((const GLubyte*)name);
    assert(result);
    return result;
}

static inline void initializeGl(){
    glBlendFuncSeparate = (_glBlendFuncSeparate) getProcAddress("glBlendFuncSeparate");
    glMultiDrawArrays = (_glMultiDrawArrays) getProcAddress("glMultiDrawArrays");
    glMultiDrawElements = (_glMultiDrawElements) getProcAddress("glMultiDrawElements");
    glPointParameterf = (_glPointParameterf) getProcAddress("glPointParameterf");
    glPointParameterfv = (_glPointParameterfv) getProcAddress("glPointParameterfv");
    glPointParameteri = (_glPointParameteri) getProcAddress("glPointParameteri");
    glPointParameteriv = (_glPointParameteriv) getProcAddress("glPointParameteriv");
    glBlendColor = (_glBlendColor) getProcAddress("glBlendColor");
    glBlendEquation = (_glBlendEquation) getProcAddress("glBlendEquation");

    glBlendEquationiARB = (_glBlendEquationiARB) getProcAddress("glBlendEquationiARB");
    glBlendEquationSeparateiARB = (_glBlendEquationSeparateiARB) getProcAddress("glBlendEquationSeparateiARB");
    glBlendFunciARB = (_glBlendFunciARB) getProcAddress("glBlendFunciARB");
    glBlendFuncSeparateiARB = (_glBlendFuncSeparateiARB) getProcAddress("glBlendFuncSeparateiARB");

    glMinSampleShading = (_glMinSampleShading) getProcAddress("glMinSampleShading");
    glBlendEquationi = (_glBlendEquationi) getProcAddress("glBlendEquationi");
    glBlendEquationSeparatei = (_glBlendEquationSeparatei) getProcAddress("glBlendEquationSeparatei");
    glBlendFunci = (_glBlendFunci) getProcAddress("glBlendFunci");
    glBlendFuncSeparatei = (_glBlendFuncSeparatei) getProcAddress("glBlendFuncSeparatei");
    glDrawArraysIndirect = (_glDrawArraysIndirect) getProcAddress("glDrawArraysIndirect");
    glDrawElementsIndirect = (_glDrawElementsIndirect) getProcAddress("glDrawElementsIndirect");
    glUniform1d = (_glUniform1d) getProcAddress("glUniform1d");
    glUniform2d = (_glUniform2d) getProcAddress("glUniform2d");
    glUniform3d = (_glUniform3d) getProcAddress("glUniform3d");
    glUniform4d = (_glUniform4d) getProcAddress("glUniform4d");
    glUniform1dv = (_glUniform1dv) getProcAddress("glUniform1dv");
    glUniform2dv = (_glUniform2dv) getProcAddress("glUniform2dv");
    glUniform3dv = (_glUniform3dv) getProcAddress("glUniform3dv");
    glUniform4dv = (_glUniform4dv) getProcAddress("glUniform4dv");
    glUniformMatrix2dv = (_glUniformMatrix2dv) getProcAddress("glUniformMatrix2dv");
    glUniformMatrix3dv = (_glUniformMatrix3dv) getProcAddress("glUniformMatrix3dv");
    glUniformMatrix4dv = (_glUniformMatrix4dv) getProcAddress("glUniformMatrix4dv");
    glUniformMatrix2x3dv = (_glUniformMatrix2x3dv) getProcAddress("glUniformMatrix2x3dv");
    glUniformMatrix2x4dv = (_glUniformMatrix2x4dv) getProcAddress("glUniformMatrix2x4dv");
    glUniformMatrix3x2dv = (_glUniformMatrix3x2dv) getProcAddress("glUniformMatrix3x2dv");
    glUniformMatrix3x4dv = (_glUniformMatrix3x4dv) getProcAddress("glUniformMatrix3x4dv");
    glUniformMatrix4x2dv = (_glUniformMatrix4x2dv) getProcAddress("glUniformMatrix4x2dv");
    glUniformMatrix4x3dv = (_glUniformMatrix4x3dv) getProcAddress("glUniformMatrix4x3dv");
    glGetUniformdv = (_glGetUniformdv) getProcAddress("glGetUniformdv");
    glGetSubroutineUniformLocation = (_glGetSubroutineUniformLocation) getProcAddress("glGetSubroutineUniformLocation");
    glGetSubroutineIndex = (_glGetSubroutineIndex) getProcAddress("glGetSubroutineIndex");
    glGetActiveSubroutineUniformiv = (_glGetActiveSubroutineUniformiv) getProcAddress("glGetActiveSubroutineUniformiv");
    glGetActiveSubroutineUniformName = (_glGetActiveSubroutineUniformName) getProcAddress("glGetActiveSubroutineUniformName");
    glGetActiveSubroutineName = (_glGetActiveSubroutineName) getProcAddress("glGetActiveSubroutineName");
    glUniformSubroutinesuiv = (_glUniformSubroutinesuiv) getProcAddress("glUniformSubroutinesuiv");
    glGetUniformSubroutineuiv = (_glGetUniformSubroutineuiv) getProcAddress("glGetUniformSubroutineuiv");
    glGetProgramStageiv = (_glGetProgramStageiv) getProcAddress("glGetProgramStageiv");
    glPatchParameteri = (_glPatchParameteri) getProcAddress("glPatchParameteri");
    glPatchParameterfv = (_glPatchParameterfv) getProcAddress("glPatchParameterfv");
    glBindTransformFeedback = (_glBindTransformFeedback) getProcAddress("glBindTransformFeedback");
    glDeleteTransformFeedbacks = (_glDeleteTransformFeedbacks) getProcAddress("glDeleteTransformFeedbacks");
    glGenTransformFeedbacks = (_glGenTransformFeedbacks) getProcAddress("glGenTransformFeedbacks");
    glIsTransformFeedback = (_glIsTransformFeedback) getProcAddress("glIsTransformFeedback");
    glPauseTransformFeedback = (_glPauseTransformFeedback) getProcAddress("glPauseTransformFeedback");
    glResumeTransformFeedback = (_glResumeTransformFeedback) getProcAddress("glResumeTransformFeedback");
    glDrawTransformFeedback = (_glDrawTransformFeedback) getProcAddress("glDrawTransformFeedback");
    glDrawTransformFeedbackStream = (_glDrawTransformFeedbackStream) getProcAddress("glDrawTransformFeedbackStream");
    glBeginQueryIndexed = (_glBeginQueryIndexed) getProcAddress("glBeginQueryIndexed");
    glEndQueryIndexed = (_glEndQueryIndexed) getProcAddress("glEndQueryIndexed");
    glGetQueryIndexediv = (_glGetQueryIndexediv) getProcAddress("glGetQueryIndexediv");

    glDrawElementsBaseVertex = (_glDrawElementsBaseVertex) getProcAddress("glDrawElementsBaseVertex");
    glDrawRangeElementsBaseVertex = (_glDrawRangeElementsBaseVertex) getProcAddress("glDrawRangeElementsBaseVertex");
    glDrawElementsInstancedBaseVertex = (_glDrawElementsInstancedBaseVertex) getProcAddress("glDrawElementsInstancedBaseVertex");
    glMultiDrawElementsBaseVertex = (_glMultiDrawElementsBaseVertex) getProcAddress("glMultiDrawElementsBaseVertex");
    glProvokingVertex = (_glProvokingVertex) getProcAddress("glProvokingVertex");
    glFenceSync = (_glFenceSync) getProcAddress("glFenceSync");
    glIsSync = (_glIsSync) getProcAddress("glIsSync");
    glDeleteSync = (_glDeleteSync) getProcAddress("glDeleteSync");
    glClientWaitSync = (_glClientWaitSync) getProcAddress("glClientWaitSync");
    glWaitSync = (_glWaitSync) getProcAddress("glWaitSync");
    glGetInteger64v = (_glGetInteger64v) getProcAddress("glGetInteger64v");
    glGetSynciv = (_glGetSynciv) getProcAddress("glGetSynciv");
    glGetInteger64i_v = (_glGetInteger64i_v) getProcAddress("glGetInteger64i_v");
    glGetBufferParameteri64v = (_glGetBufferParameteri64v) getProcAddress("glGetBufferParameteri64v");
    glFramebufferTexture = (_glFramebufferTexture) getProcAddress("glFramebufferTexture");
    glTexImage2DMultisample = (_glTexImage2DMultisample) getProcAddress("glTexImage2DMultisample");
    glTexImage3DMultisample = (_glTexImage3DMultisample) getProcAddress("glTexImage3DMultisample");
    glGetMultisamplefv = (_glGetMultisamplefv) getProcAddress("glGetMultisamplefv");
    glSampleMaski = (_glSampleMaski) getProcAddress("glSampleMaski");

    glGenQueries = (_glGenQueries) getProcAddress("glGenQueries");
    glDeleteQueries = (_glDeleteQueries) getProcAddress("glDeleteQueries");
    glIsQuery = (_glIsQuery) getProcAddress("glIsQuery");
    glBeginQuery = (_glBeginQuery) getProcAddress("glBeginQuery");
    glEndQuery = (_glEndQuery) getProcAddress("glEndQuery");
    glGetQueryiv = (_glGetQueryiv) getProcAddress("glGetQueryiv");
    glGetQueryObjectiv = (_glGetQueryObjectiv) getProcAddress("glGetQueryObjectiv");
    glGetQueryObjectuiv = (_glGetQueryObjectuiv) getProcAddress("glGetQueryObjectuiv");
    glBindBuffer = (_glBindBuffer) getProcAddress("glBindBuffer");
    glDeleteBuffers = (_glDeleteBuffers) getProcAddress("glDeleteBuffers");
    glGenBuffers = (_glGenBuffers) getProcAddress("glGenBuffers");
    glIsBuffer = (_glIsBuffer) getProcAddress("glIsBuffer");
    glBufferData = (_glBufferData) getProcAddress("glBufferData");
    glBufferSubData = (_glBufferSubData) getProcAddress("glBufferSubData");
    glGetBufferSubData = (_glGetBufferSubData) getProcAddress("glGetBufferSubData");
    glMapBuffer = (_glMapBuffer) getProcAddress("glMapBuffer");
    glUnmapBuffer = (_glUnmapBuffer) getProcAddress("glUnmapBuffer");
    glGetBufferParameteriv = (_glGetBufferParameteriv) getProcAddress("glGetBufferParameteriv");
    glGetBufferPointerv = (_glGetBufferPointerv) getProcAddress("glGetBufferPointerv");

    glColorMaski = (_glColorMaski) getProcAddress("glColorMaski");
    glGetBooleani_v = (_glGetBooleani_v) getProcAddress("glGetBooleani_v");
    glGetIntegeri_v = (_glGetIntegeri_v) getProcAddress("glGetIntegeri_v");
    glEnablei = (_glEnablei) getProcAddress("glEnablei");
    glDisablei = (_glDisablei) getProcAddress("glDisablei");
    glIsEnabledi = (_glIsEnabledi) getProcAddress("glIsEnabledi");
    glBeginTransformFeedback = (_glBeginTransformFeedback) getProcAddress("glBeginTransformFeedback");
    glEndTransformFeedback = (_glEndTransformFeedback) getProcAddress("glEndTransformFeedback");
    glBindBufferRange = (_glBindBufferRange) getProcAddress("glBindBufferRange");
    glBindBufferBase = (_glBindBufferBase) getProcAddress("glBindBufferBase");
    glTransformFeedbackVaryings = (_glTransformFeedbackVaryings) getProcAddress("glTransformFeedbackVaryings");
    glGetTransformFeedbackVarying = (_glGetTransformFeedbackVarying) getProcAddress("glGetTransformFeedbackVarying");
    glClampColor = (_glClampColor) getProcAddress("glClampColor");
    glBeginConditionalRender = (_glBeginConditionalRender) getProcAddress("glBeginConditionalRender");
    glEndConditionalRender = (_glEndConditionalRender) getProcAddress("glEndConditionalRender");
    glVertexAttribIPointer = (_glVertexAttribIPointer) getProcAddress("glVertexAttribIPointer");
    glGetVertexAttribIiv = (_glGetVertexAttribIiv) getProcAddress("glGetVertexAttribIiv");
    glGetVertexAttribIuiv = (_glGetVertexAttribIuiv) getProcAddress("glGetVertexAttribIuiv");
    glVertexAttribI1i = (_glVertexAttribI1i) getProcAddress("glVertexAttribI1i");
    glVertexAttribI2i = (_glVertexAttribI2i) getProcAddress("glVertexAttribI2i");
    glVertexAttribI3i = (_glVertexAttribI3i) getProcAddress("glVertexAttribI3i");
    glVertexAttribI4i = (_glVertexAttribI4i) getProcAddress("glVertexAttribI4i");
    glVertexAttribI1ui = (_glVertexAttribI1ui) getProcAddress("glVertexAttribI1ui");
    glVertexAttribI2ui = (_glVertexAttribI2ui) getProcAddress("glVertexAttribI2ui");
    glVertexAttribI3ui = (_glVertexAttribI3ui) getProcAddress("glVertexAttribI3ui");
    glVertexAttribI4ui = (_glVertexAttribI4ui) getProcAddress("glVertexAttribI4ui");
    glVertexAttribI1iv = (_glVertexAttribI1iv) getProcAddress("glVertexAttribI1iv");
    glVertexAttribI2iv = (_glVertexAttribI2iv) getProcAddress("glVertexAttribI2iv");
    glVertexAttribI3iv = (_glVertexAttribI3iv) getProcAddress("glVertexAttribI3iv");
    glVertexAttribI4iv = (_glVertexAttribI4iv) getProcAddress("glVertexAttribI4iv");
    glVertexAttribI1uiv = (_glVertexAttribI1uiv) getProcAddress("glVertexAttribI1uiv");
    glVertexAttribI2uiv = (_glVertexAttribI2uiv) getProcAddress("glVertexAttribI2uiv");
    glVertexAttribI3uiv = (_glVertexAttribI3uiv) getProcAddress("glVertexAttribI3uiv");
    glVertexAttribI4uiv = (_glVertexAttribI4uiv) getProcAddress("glVertexAttribI4uiv");
    glVertexAttribI4bv = (_glVertexAttribI4bv) getProcAddress("glVertexAttribI4bv");
    glVertexAttribI4sv = (_glVertexAttribI4sv) getProcAddress("glVertexAttribI4sv");
    glVertexAttribI4ubv = (_glVertexAttribI4ubv) getProcAddress("glVertexAttribI4ubv");
    glVertexAttribI4usv = (_glVertexAttribI4usv) getProcAddress("glVertexAttribI4usv");
    glGetUniformuiv = (_glGetUniformuiv) getProcAddress("glGetUniformuiv");
    glBindFragDataLocation = (_glBindFragDataLocation) getProcAddress("glBindFragDataLocation");
    glGetFragDataLocation = (_glGetFragDataLocation) getProcAddress("glGetFragDataLocation");
    glUniform1ui = (_glUniform1ui) getProcAddress("glUniform1ui");
    glUniform2ui = (_glUniform2ui) getProcAddress("glUniform2ui");
    glUniform3ui = (_glUniform3ui) getProcAddress("glUniform3ui");
    glUniform4ui = (_glUniform4ui) getProcAddress("glUniform4ui");
    glUniform1uiv = (_glUniform1uiv) getProcAddress("glUniform1uiv");
    glUniform2uiv = (_glUniform2uiv) getProcAddress("glUniform2uiv");
    glUniform3uiv = (_glUniform3uiv) getProcAddress("glUniform3uiv");
    glUniform4uiv = (_glUniform4uiv) getProcAddress("glUniform4uiv");
    glTexParameterIiv = (_glTexParameterIiv) getProcAddress("glTexParameterIiv");
    glTexParameterIuiv = (_glTexParameterIuiv) getProcAddress("glTexParameterIuiv");
    glGetTexParameterIiv = (_glGetTexParameterIiv) getProcAddress("glGetTexParameterIiv");
    glGetTexParameterIuiv = (_glGetTexParameterIuiv) getProcAddress("glGetTexParameterIuiv");
    glClearBufferiv = (_glClearBufferiv) getProcAddress("glClearBufferiv");
    glClearBufferuiv = (_glClearBufferuiv) getProcAddress("glClearBufferuiv");
    glClearBufferfv = (_glClearBufferfv) getProcAddress("glClearBufferfv");
    glClearBufferfi = (_glClearBufferfi) getProcAddress("glClearBufferfi");
    glGetStringi = (_glGetStringi) getProcAddress("glGetStringi");
    glIsRenderbuffer = (_glIsRenderbuffer) getProcAddress("glIsRenderbuffer");
    glBindRenderbuffer = (_glBindRenderbuffer) getProcAddress("glBindRenderbuffer");
    glDeleteRenderbuffers = (_glDeleteRenderbuffers) getProcAddress("glDeleteRenderbuffers");
    glGenRenderbuffers = (_glGenRenderbuffers) getProcAddress("glGenRenderbuffers");
    glRenderbufferStorage = (_glRenderbufferStorage) getProcAddress("glRenderbufferStorage");
    glGetRenderbufferParameteriv = (_glGetRenderbufferParameteriv) getProcAddress("glGetRenderbufferParameteriv");
    glIsFramebuffer = (_glIsFramebuffer) getProcAddress("glIsFramebuffer");
    glBindFramebuffer = (_glBindFramebuffer) getProcAddress("glBindFramebuffer");
    glDeleteFramebuffers = (_glDeleteFramebuffers) getProcAddress("glDeleteFramebuffers");
    glGenFramebuffers = (_glGenFramebuffers) getProcAddress("glGenFramebuffers");
    glCheckFramebufferStatus = (_glCheckFramebufferStatus) getProcAddress("glCheckFramebufferStatus");
    glFramebufferTexture1D = (_glFramebufferTexture1D) getProcAddress("glFramebufferTexture1D");
    glFramebufferTexture2D = (_glFramebufferTexture2D) getProcAddress("glFramebufferTexture2D");
    glFramebufferTexture3D = (_glFramebufferTexture3D) getProcAddress("glFramebufferTexture3D");
    glFramebufferRenderbuffer = (_glFramebufferRenderbuffer) getProcAddress("glFramebufferRenderbuffer");
    glGetFramebufferAttachmentParameteriv = (_glGetFramebufferAttachmentParameteriv) getProcAddress("glGetFramebufferAttachmentParameteriv");
    glGenerateMipmap = (_glGenerateMipmap) getProcAddress("glGenerateMipmap");
    glBlitFramebuffer = (_glBlitFramebuffer) getProcAddress("glBlitFramebuffer");
    glRenderbufferStorageMultisample = (_glRenderbufferStorageMultisample) getProcAddress("glRenderbufferStorageMultisample");
    glFramebufferTextureLayer = (_glFramebufferTextureLayer) getProcAddress("glFramebufferTextureLayer");
    glMapBufferRange = (_glMapBufferRange) getProcAddress("glMapBufferRange");
    glFlushMappedBufferRange = (_glFlushMappedBufferRange) getProcAddress("glFlushMappedBufferRange");
    glBindVertexArray = (_glBindVertexArray) getProcAddress("glBindVertexArray");
    glDeleteVertexArrays = (_glDeleteVertexArrays) getProcAddress("glDeleteVertexArrays");
    glGenVertexArrays = (_glGenVertexArrays) getProcAddress("glGenVertexArrays");
    glIsVertexArray = (_glIsVertexArray) getProcAddress("glIsVertexArray");

    glBindFragDataLocationIndexed = (_glBindFragDataLocationIndexed) getProcAddress("glBindFragDataLocationIndexed");
    glGetFragDataIndex = (_glGetFragDataIndex) getProcAddress("glGetFragDataIndex");
    glGenSamplers = (_glGenSamplers) getProcAddress("glGenSamplers");
    glDeleteSamplers = (_glDeleteSamplers) getProcAddress("glDeleteSamplers");
    glIsSampler = (_glIsSampler) getProcAddress("glIsSampler");
    glBindSampler = (_glBindSampler) getProcAddress("glBindSampler");
    glSamplerParameteri = (_glSamplerParameteri) getProcAddress("glSamplerParameteri");
    glSamplerParameteriv = (_glSamplerParameteriv) getProcAddress("glSamplerParameteriv");
    glSamplerParameterf = (_glSamplerParameterf) getProcAddress("glSamplerParameterf");
    glSamplerParameterfv = (_glSamplerParameterfv) getProcAddress("glSamplerParameterfv");
    glSamplerParameterIiv = (_glSamplerParameterIiv) getProcAddress("glSamplerParameterIiv");
    glSamplerParameterIuiv = (_glSamplerParameterIuiv) getProcAddress("glSamplerParameterIuiv");
    glGetSamplerParameteriv = (_glGetSamplerParameteriv) getProcAddress("glGetSamplerParameteriv");
    glGetSamplerParameterIiv = (_glGetSamplerParameterIiv) getProcAddress("glGetSamplerParameterIiv");
    glGetSamplerParameterfv = (_glGetSamplerParameterfv) getProcAddress("glGetSamplerParameterfv");
    glGetSamplerParameterIuiv = (_glGetSamplerParameterIuiv) getProcAddress("glGetSamplerParameterIuiv");
    glQueryCounter = (_glQueryCounter) getProcAddress("glQueryCounter");
    glGetQueryObjecti64v = (_glGetQueryObjecti64v) getProcAddress("glGetQueryObjecti64v");
    glGetQueryObjectui64v = (_glGetQueryObjectui64v) getProcAddress("glGetQueryObjectui64v");
    glVertexAttribDivisor = (_glVertexAttribDivisor) getProcAddress("glVertexAttribDivisor");
    glVertexAttribP1ui = (_glVertexAttribP1ui) getProcAddress("glVertexAttribP1ui");
    glVertexAttribP1uiv = (_glVertexAttribP1uiv) getProcAddress("glVertexAttribP1uiv");
    glVertexAttribP2ui = (_glVertexAttribP2ui) getProcAddress("glVertexAttribP2ui");
    glVertexAttribP2uiv = (_glVertexAttribP2uiv) getProcAddress("glVertexAttribP2uiv");
    glVertexAttribP3ui = (_glVertexAttribP3ui) getProcAddress("glVertexAttribP3ui");
    glVertexAttribP3uiv = (_glVertexAttribP3uiv) getProcAddress("glVertexAttribP3uiv");
    glVertexAttribP4ui = (_glVertexAttribP4ui) getProcAddress("glVertexAttribP4ui");
    glVertexAttribP4uiv = (_glVertexAttribP4uiv) getProcAddress("glVertexAttribP4uiv");
    glBlendEquationSeparate = (_glBlendEquationSeparate) getProcAddress("glBlendEquationSeparate");
    glDrawBuffers = (_glDrawBuffers) getProcAddress("glDrawBuffers");
    glStencilOpSeparate = (_glStencilOpSeparate) getProcAddress("glStencilOpSeparate");
    glStencilFuncSeparate = (_glStencilFuncSeparate) getProcAddress("glStencilFuncSeparate");
    glStencilMaskSeparate = (_glStencilMaskSeparate) getProcAddress("glStencilMaskSeparate");
    glAttachShader = (_glAttachShader) getProcAddress("glAttachShader");
    glBindAttribLocation = (_glBindAttribLocation) getProcAddress("glBindAttribLocation");
    glCompileShader = (_glCompileShader) getProcAddress("glCompileShader");
    glCreateProgram = (_glCreateProgram) getProcAddress("glCreateProgram");
    _inferno_glCreateShader = (_glCreateShader) getProcAddress("glCreateShader");
    glDeleteProgram = (_glDeleteProgram) getProcAddress("glDeleteProgram");
    glDeleteShader = (_glDeleteShader) getProcAddress("glDeleteShader");
    glDetachShader = (_glDetachShader) getProcAddress("glDetachShader");
    glDisableVertexAttribArray = (_glDisableVertexAttribArray) getProcAddress("glDisableVertexAttribArray");
    glEnableVertexAttribArray = (_glEnableVertexAttribArray) getProcAddress("glEnableVertexAttribArray");
    glGetActiveAttrib = (_glGetActiveAttrib) getProcAddress("glGetActiveAttrib");
    glGetActiveUniform = (_glGetActiveUniform) getProcAddress("glGetActiveUniform");
    glGetAttachedShaders = (_glGetAttachedShaders) getProcAddress("glGetAttachedShaders");
    glGetAttribLocation = (_glGetAttribLocation) getProcAddress("glGetAttribLocation");
    glGetProgramiv = (_glGetProgramiv) getProcAddress("glGetProgramiv");
    glGetProgramInfoLog = (_glGetProgramInfoLog) getProcAddress("glGetProgramInfoLog");
    glGetShaderiv = (_glGetShaderiv) getProcAddress("glGetShaderiv");
    glGetShaderInfoLog = (_glGetShaderInfoLog) getProcAddress("glGetShaderInfoLog");
    glGetShaderSource = (_glGetShaderSource) getProcAddress("glGetShaderSource");
    glGetUniformLocation = (_glGetUniformLocation) getProcAddress("glGetUniformLocation");
    glGetUniformfv = (_glGetUniformfv) getProcAddress("glGetUniformfv");
    glGetUniformiv = (_glGetUniformiv) getProcAddress("glGetUniformiv");
    glGetVertexAttribdv = (_glGetVertexAttribdv) getProcAddress("glGetVertexAttribdv");
    glGetVertexAttribfv = (_glGetVertexAttribfv) getProcAddress("glGetVertexAttribfv");
    glGetVertexAttribiv = (_glGetVertexAttribiv) getProcAddress("glGetVertexAttribiv");
    glGetVertexAttribPointerv = (_glGetVertexAttribPointerv) getProcAddress("glGetVertexAttribPointerv");
    glIsProgram = (_glIsProgram) getProcAddress("glIsProgram");
    glIsShader = (_glIsShader) getProcAddress("glIsShader");
    glLinkProgram = (_glLinkProgram) getProcAddress("glLinkProgram");
    glShaderSource = (_glShaderSource) getProcAddress("glShaderSource");
    glUseProgram = (_glUseProgram) getProcAddress("glUseProgram");
    glUniform1f = (_glUniform1f) getProcAddress("glUniform1f");
    glUniform2f = (_glUniform2f) getProcAddress("glUniform2f");
    glUniform3f = (_glUniform3f) getProcAddress("glUniform3f");
    glUniform4f = (_glUniform4f) getProcAddress("glUniform4f");
    glUniform1i = (_glUniform1i) getProcAddress("glUniform1i");
    glUniform2i = (_glUniform2i) getProcAddress("glUniform2i");
    glUniform3i = (_glUniform3i) getProcAddress("glUniform3i");
    glUniform4i = (_glUniform4i) getProcAddress("glUniform4i");
    glUniform1fv = (_glUniform1fv) getProcAddress("glUniform1fv");
    glUniform2fv = (_glUniform2fv) getProcAddress("glUniform2fv");
    glUniform3fv = (_glUniform3fv) getProcAddress("glUniform3fv");
    glUniform4fv = (_glUniform4fv) getProcAddress("glUniform4fv");
    glUniform1iv = (_glUniform1iv) getProcAddress("glUniform1iv");
    glUniform2iv = (_glUniform2iv) getProcAddress("glUniform2iv");
    glUniform3iv = (_glUniform3iv) getProcAddress("glUniform3iv");
    glUniform4iv = (_glUniform4iv) getProcAddress("glUniform4iv");
    glUniformMatrix2fv = (_glUniformMatrix2fv) getProcAddress("glUniformMatrix2fv");
    glUniformMatrix3fv = (_glUniformMatrix3fv) getProcAddress("glUniformMatrix3fv");
    glUniformMatrix4fv = (_glUniformMatrix4fv) getProcAddress("glUniformMatrix4fv");
    glValidateProgram = (_glValidateProgram) getProcAddress("glValidateProgram");
    glVertexAttrib1d = (_glVertexAttrib1d) getProcAddress("glVertexAttrib1d");
    glVertexAttrib1dv = (_glVertexAttrib1dv) getProcAddress("glVertexAttrib1dv");
    glVertexAttrib1f = (_glVertexAttrib1f) getProcAddress("glVertexAttrib1f");
    glVertexAttrib1fv = (_glVertexAttrib1fv) getProcAddress("glVertexAttrib1fv");
    glVertexAttrib1s = (_glVertexAttrib1s) getProcAddress("glVertexAttrib1s");
    glVertexAttrib1sv = (_glVertexAttrib1sv) getProcAddress("glVertexAttrib1sv");
    glVertexAttrib2d = (_glVertexAttrib2d) getProcAddress("glVertexAttrib2d");
    glVertexAttrib2dv = (_glVertexAttrib2dv) getProcAddress("glVertexAttrib2dv");
    glVertexAttrib2f = (_glVertexAttrib2f) getProcAddress("glVertexAttrib2f");
    glVertexAttrib2fv = (_glVertexAttrib2fv) getProcAddress("glVertexAttrib2fv");
    glVertexAttrib2s = (_glVertexAttrib2s) getProcAddress("glVertexAttrib2s");
    glVertexAttrib2sv = (_glVertexAttrib2sv) getProcAddress("glVertexAttrib2sv");
    glVertexAttrib3d = (_glVertexAttrib3d) getProcAddress("glVertexAttrib3d");
    glVertexAttrib3dv = (_glVertexAttrib3dv) getProcAddress("glVertexAttrib3dv");
    glVertexAttrib3f = (_glVertexAttrib3f) getProcAddress("glVertexAttrib3f");
    glVertexAttrib3fv = (_glVertexAttrib3fv) getProcAddress("glVertexAttrib3fv");
    glVertexAttrib3s = (_glVertexAttrib3s) getProcAddress("glVertexAttrib3s");
    glVertexAttrib3sv = (_glVertexAttrib3sv) getProcAddress("glVertexAttrib3sv");
    glVertexAttrib4Nbv = (_glVertexAttrib4Nbv) getProcAddress("glVertexAttrib4Nbv");
    glVertexAttrib4Niv = (_glVertexAttrib4Niv) getProcAddress("glVertexAttrib4Niv");
    glVertexAttrib4Nsv = (_glVertexAttrib4Nsv) getProcAddress("glVertexAttrib4Nsv");
    glVertexAttrib4Nub = (_glVertexAttrib4Nub) getProcAddress("glVertexAttrib4Nub");
    glVertexAttrib4Nubv = (_glVertexAttrib4Nubv) getProcAddress("glVertexAttrib4Nubv");
    glVertexAttrib4Nuiv = (_glVertexAttrib4Nuiv) getProcAddress("glVertexAttrib4Nuiv");
    glVertexAttrib4Nusv = (_glVertexAttrib4Nusv) getProcAddress("glVertexAttrib4Nusv");
    glVertexAttrib4bv = (_glVertexAttrib4bv) getProcAddress("glVertexAttrib4bv");
    glVertexAttrib4d = (_glVertexAttrib4d) getProcAddress("glVertexAttrib4d");
    glVertexAttrib4dv = (_glVertexAttrib4dv) getProcAddress("glVertexAttrib4dv");
    glVertexAttrib4f = (_glVertexAttrib4f) getProcAddress("glVertexAttrib4f");
    glVertexAttrib4fv = (_glVertexAttrib4fv) getProcAddress("glVertexAttrib4fv");
    glVertexAttrib4iv = (_glVertexAttrib4iv) getProcAddress("glVertexAttrib4iv");
    glVertexAttrib4s = (_glVertexAttrib4s) getProcAddress("glVertexAttrib4s");
    glVertexAttrib4sv = (_glVertexAttrib4sv) getProcAddress("glVertexAttrib4sv");
    glVertexAttrib4ubv = (_glVertexAttrib4ubv) getProcAddress("glVertexAttrib4ubv");
    glVertexAttrib4uiv = (_glVertexAttrib4uiv) getProcAddress("glVertexAttrib4uiv");
    glVertexAttrib4usv = (_glVertexAttrib4usv) getProcAddress("glVertexAttrib4usv");
    glVertexAttribPointer = (_glVertexAttribPointer) getProcAddress("glVertexAttribPointer");

    glClearBufferData = (_glClearBufferData) getProcAddress("glClearBufferData");
    glClearBufferSubData = (_glClearBufferSubData) getProcAddress("glClearBufferSubData");
    glDispatchCompute = (_glDispatchCompute) getProcAddress("glDispatchCompute");
    glDispatchComputeIndirect = (_glDispatchComputeIndirect) getProcAddress("glDispatchComputeIndirect");
    glCopyImageSubData = (_glCopyImageSubData) getProcAddress("glCopyImageSubData");
    glFramebufferParameteri = (_glFramebufferParameteri) getProcAddress("glFramebufferParameteri");
    glGetFramebufferParameteriv = (_glGetFramebufferParameteriv) getProcAddress("glGetFramebufferParameteriv");
    glGetInternalformati64v = (_glGetInternalformati64v) getProcAddress("glGetInternalformati64v");
    glInvalidateTexSubImage = (_glInvalidateTexSubImage) getProcAddress("glInvalidateTexSubImage");
    glInvalidateTexImage = (_glInvalidateTexImage) getProcAddress("glInvalidateTexImage");
    glInvalidateBufferSubData = (_glInvalidateBufferSubData) getProcAddress("glInvalidateBufferSubData");
    glInvalidateBufferData = (_glInvalidateBufferData) getProcAddress("glInvalidateBufferData");
    glInvalidateFramebuffer = (_glInvalidateFramebuffer) getProcAddress("glInvalidateFramebuffer");
    glInvalidateSubFramebuffer = (_glInvalidateSubFramebuffer) getProcAddress("glInvalidateSubFramebuffer");
    glMultiDrawArraysIndirect = (_glMultiDrawArraysIndirect) getProcAddress("glMultiDrawArraysIndirect");
    glMultiDrawElementsIndirect = (_glMultiDrawElementsIndirect) getProcAddress("glMultiDrawElementsIndirect");
    glGetProgramInterfaceiv = (_glGetProgramInterfaceiv) getProcAddress("glGetProgramInterfaceiv");
    glGetProgramResourceIndex = (_glGetProgramResourceIndex) getProcAddress("glGetProgramResourceIndex");
    glGetProgramResourceName = (_glGetProgramResourceName) getProcAddress("glGetProgramResourceName");
    glGetProgramResourceiv = (_glGetProgramResourceiv) getProcAddress("glGetProgramResourceiv");
    glGetProgramResourceLocation = (_glGetProgramResourceLocation) getProcAddress("glGetProgramResourceLocation");
    glGetProgramResourceLocationIndex = (_glGetProgramResourceLocationIndex) getProcAddress("glGetProgramResourceLocationIndex");
    glShaderStorageBlockBinding = (_glShaderStorageBlockBinding) getProcAddress("glShaderStorageBlockBinding");
    glTexBufferRange = (_glTexBufferRange) getProcAddress("glTexBufferRange");
    glTexStorage2DMultisample = (_glTexStorage2DMultisample) getProcAddress("glTexStorage2DMultisample");
    glTexStorage3DMultisample = (_glTexStorage3DMultisample) getProcAddress("glTexStorage3DMultisample");
    glTextureView = (_glTextureView) getProcAddress("glTextureView");
    glBindVertexBuffer = (_glBindVertexBuffer) getProcAddress("glBindVertexBuffer");
    glVertexAttribFormat = (_glVertexAttribFormat) getProcAddress("glVertexAttribFormat");
    glVertexAttribIFormat = (_glVertexAttribIFormat) getProcAddress("glVertexAttribIFormat");
    glVertexAttribLFormat = (_glVertexAttribLFormat) getProcAddress("glVertexAttribLFormat");
    glVertexAttribBinding = (_glVertexAttribBinding) getProcAddress("glVertexAttribBinding");
    glVertexBindingDivisor = (_glVertexBindingDivisor) getProcAddress("glVertexBindingDivisor");
    glDebugMessageControl = (_glDebugMessageControl) getProcAddress("glDebugMessageControl");
    glDebugMessageInsert = (_glDebugMessageInsert) getProcAddress("glDebugMessageInsert");
    glDebugMessageCallback = (_glDebugMessageCallback) getProcAddress("glDebugMessageCallback");
    glGetDebugMessageLog = (_glGetDebugMessageLog) getProcAddress("glGetDebugMessageLog");
    glPushDebugGroup = (_glPushDebugGroup) getProcAddress("glPushDebugGroup");
    glPopDebugGroup = (_glPopDebugGroup) getProcAddress("glPopDebugGroup");
    glObjectLabel = (_glObjectLabel) getProcAddress("glObjectLabel");
    glGetObjectLabel = (_glGetObjectLabel) getProcAddress("glGetObjectLabel");
    glObjectPtrLabel = (_glObjectPtrLabel) getProcAddress("glObjectPtrLabel");
    glGetObjectPtrLabel = (_glGetObjectPtrLabel) getProcAddress("glGetObjectPtrLabel");
    glBindVertexBuffer = (_glBindVertexBuffer) getProcAddress("glBindVertexBuffer");
    glUnmapNamedBuffer = (_glUnmapNamedBuffer) getProcAddress("glUnmapNamedBuffer");
    glClipControl = (_glClipControl) getProcAddress("glClipControl");
    glCreateTransformFeedbacks = (_glCreateTransformFeedbacks) getProcAddress("glCreateTransformFeedbacks");
    glTransformFeedbackBufferBase = (_glTransformFeedbackBufferBase) getProcAddress("glTransformFeedbackBufferBase");
    glTransformFeedbackBufferRange = (_glTransformFeedbackBufferRange) getProcAddress("glTransformFeedbackBufferRange");
    glGetTransformFeedbackiv = (_glGetTransformFeedbackiv) getProcAddress("glGetTransformFeedbackiv");
    glGetTransformFeedbacki_v = (_glGetTransformFeedbacki_v) getProcAddress("glGetTransformFeedbacki_v");
    glGetTransformFeedbacki64_v = (_glGetTransformFeedbacki64_v) getProcAddress("glGetTransformFeedbacki64_v");
    glCreateBuffers = (_glCreateBuffers) getProcAddress("glCreateBuffers");
    glNamedBufferStorage = (_glNamedBufferStorage) getProcAddress("glNamedBufferStorage");
    glNamedBufferData = (_glNamedBufferData) getProcAddress("glNamedBufferData");
    glNamedBufferSubData = (_glNamedBufferSubData) getProcAddress("glNamedBufferSubData");
    glCopyNamedBufferSubData = (_glCopyNamedBufferSubData) getProcAddress("glCopyNamedBufferSubData");
    glClearNamedBufferData = (_glClearNamedBufferData) getProcAddress("glClearNamedBufferData");
    glClearNamedBufferSubData = (_glClearNamedBufferSubData) getProcAddress("glClearNamedBufferSubData");
    glFlushMappedNamedBufferRange = (_glFlushMappedNamedBufferRange) getProcAddress("glFlushMappedNamedBufferRange");
    glGetNamedBufferParameteriv = (_glGetNamedBufferParameteriv) getProcAddress("glGetNamedBufferParameteriv");
    glGetNamedBufferParameteri64v = (_glGetNamedBufferParameteri64v) getProcAddress("glGetNamedBufferParameteri64v");
    glGetNamedBufferPointerv = (_glGetNamedBufferPointerv) getProcAddress("glGetNamedBufferPointerv");
    glGetNamedBufferSubData = (_glGetNamedBufferSubData) getProcAddress("glGetNamedBufferSubData");
    glCreateFramebuffers = (_glCreateFramebuffers) getProcAddress("glCreateFramebuffers");
    glNamedFramebufferRenderbuffer = (_glNamedFramebufferRenderbuffer) getProcAddress("glNamedFramebufferRenderbuffer");
    glNamedFramebufferParameteri = (_glNamedFramebufferParameteri) getProcAddress("glNamedFramebufferParameteri");
    glNamedFramebufferTexture = (_glNamedFramebufferTexture) getProcAddress("glNamedFramebufferTexture");
    glNamedFramebufferTextureLayer = (_glNamedFramebufferTextureLayer) getProcAddress("glNamedFramebufferTextureLayer");
    glNamedFramebufferDrawBuffer = (_glNamedFramebufferDrawBuffer) getProcAddress("glNamedFramebufferDrawBuffer");
    glNamedFramebufferDrawBuffers = (_glNamedFramebufferDrawBuffers) getProcAddress("glNamedFramebufferDrawBuffers");
    glNamedFramebufferReadBuffer = (_glNamedFramebufferReadBuffer) getProcAddress("glNamedFramebufferReadBuffer");
    glInvalidateNamedFramebufferData = (_glInvalidateNamedFramebufferData) getProcAddress("glInvalidateNamedFramebufferData");
    glInvalidateNamedFramebufferSubData = (_glInvalidateNamedFramebufferSubData) getProcAddress("glInvalidateNamedFramebufferSubData");
    glClearNamedFramebufferiv = (_glClearNamedFramebufferiv) getProcAddress("glClearNamedFramebufferiv");
    glClearNamedFramebufferuiv = (_glClearNamedFramebufferuiv) getProcAddress("glClearNamedFramebufferuiv");
    glClearNamedFramebufferfv = (_glClearNamedFramebufferfv) getProcAddress("glClearNamedFramebufferfv");
    glClearNamedFramebufferfi = (_glClearNamedFramebufferfi) getProcAddress("glClearNamedFramebufferfi");
    glBlitNamedFramebuffer = (_glBlitNamedFramebuffer) getProcAddress("glBlitNamedFramebuffer");
    glCheckNamedFramebufferStatus = (_glCheckNamedFramebufferStatus) getProcAddress("glCheckNamedFramebufferStatus");
    glGetNamedFramebufferParameteriv = (_glGetNamedFramebufferParameteriv) getProcAddress("glGetNamedFramebufferParameteriv");
    glGetNamedFramebufferAttachmentParameteriv = (_glGetNamedFramebufferAttachmentParameteriv) getProcAddress("glGetNamedFramebufferAttachmentParameteriv");
    glCreateRenderbuffers = (_glCreateRenderbuffers) getProcAddress("glCreateRenderbuffers");
    glNamedRenderbufferStorage = (_glNamedRenderbufferStorage) getProcAddress("glNamedRenderbufferStorage");
    glNamedRenderbufferStorageMultisample = (_glNamedRenderbufferStorageMultisample) getProcAddress("glNamedRenderbufferStorageMultisample");
    glGetNamedRenderbufferParameteriv = (_glGetNamedRenderbufferParameteriv) getProcAddress("glGetNamedRenderbufferParameteriv");
    glCreateTextures = (_glCreateTextures) getProcAddress("glCreateTextures");
    glTextureBuffer = (_glTextureBuffer) getProcAddress("glTextureBuffer");
    glTextureBufferRange = (_glTextureBufferRange) getProcAddress("glTextureBufferRange");
    glTextureStorage1D = (_glTextureStorage1D) getProcAddress("glTextureStorage1D");
    glTextureStorage2D = (_glTextureStorage2D) getProcAddress("glTextureStorage2D");
    glTextureStorage3D = (_glTextureStorage3D) getProcAddress("glTextureStorage3D");
    glTextureStorage2DMultisample = (_glTextureStorage2DMultisample) getProcAddress("glTextureStorage2DMultisample");
    glTextureStorage3DMultisample = (_glTextureStorage3DMultisample) getProcAddress("glTextureStorage3DMultisample");
    glTextureSubImage1D = (_glTextureSubImage1D) getProcAddress("glTextureSubImage1D");
    glTextureSubImage2D = (_glTextureSubImage2D) getProcAddress("glTextureSubImage2D");
    glTextureSubImage3D = (_glTextureSubImage3D) getProcAddress("glTextureSubImage3D");
    glCompressedTextureSubImage1D = (_glCompressedTextureSubImage1D) getProcAddress("glCompressedTextureSubImage1D");
    glCompressedTextureSubImage2D = (_glCompressedTextureSubImage2D) getProcAddress("glCompressedTextureSubImage2D");
    glCompressedTextureSubImage3D = (_glCompressedTextureSubImage3D) getProcAddress("glCompressedTextureSubImage3D");
    glCopyTextureSubImage1D = (_glCopyTextureSubImage1D) getProcAddress("glCopyTextureSubImage1D");
    glCopyTextureSubImage2D = (_glCopyTextureSubImage2D) getProcAddress("glCopyTextureSubImage2D");
    glCopyTextureSubImage3D = (_glCopyTextureSubImage3D) getProcAddress("glCopyTextureSubImage3D");
    glTextureParameterf = (_glTextureParameterf) getProcAddress("glTextureParameterf");
    glTextureParameterfv = (_glTextureParameterfv) getProcAddress("glTextureParameterfv");
    glTextureParameteri = (_glTextureParameteri) getProcAddress("glTextureParameteri");
    glTextureParameterIiv = (_glTextureParameterIiv) getProcAddress("glTextureParameterIiv");
    glTextureParameterIuiv = (_glTextureParameterIuiv) getProcAddress("glTextureParameterIuiv");
    glTextureParameteriv = (_glTextureParameteriv) getProcAddress("glTextureParameteriv");
    glGenerateTextureMipmap = (_glGenerateTextureMipmap) getProcAddress("glGenerateTextureMipmap");
    glBindTextureUnit = (_glBindTextureUnit) getProcAddress("glBindTextureUnit");
    glGetTextureImage = (_glGetTextureImage) getProcAddress("glGetTextureImage");
    glGetCompressedTextureImage = (_glGetCompressedTextureImage) getProcAddress("glGetCompressedTextureImage");
    glGetTextureLevelParameterfv = (_glGetTextureLevelParameterfv) getProcAddress("glGetTextureLevelParameterfv");
    glGetTextureLevelParameteriv = (_glGetTextureLevelParameteriv) getProcAddress("glGetTextureLevelParameteriv");
    glGetTextureParameterfv = (_glGetTextureParameterfv) getProcAddress("glGetTextureParameterfv");
    glGetTextureParameterIiv = (_glGetTextureParameterIiv) getProcAddress("glGetTextureParameterIiv");
    glGetTextureParameterIuiv = (_glGetTextureParameterIuiv) getProcAddress("glGetTextureParameterIuiv");
    glGetTextureParameteriv = (_glGetTextureParameteriv) getProcAddress("glGetTextureParameteriv");
    glCreateVertexArrays = (_glCreateVertexArrays) getProcAddress("glCreateVertexArrays");
    glDisableVertexArrayAttrib = (_glDisableVertexArrayAttrib) getProcAddress("glDisableVertexArrayAttrib");
    glEnableVertexArrayAttrib = (_glEnableVertexArrayAttrib) getProcAddress("glEnableVertexArrayAttrib");
    glVertexArrayElementBuffer = (_glVertexArrayElementBuffer) getProcAddress("glVertexArrayElementBuffer");
    glVertexArrayVertexBuffer = (_glVertexArrayVertexBuffer) getProcAddress("glVertexArrayVertexBuffer");
    glVertexArrayVertexBuffers = (_glVertexArrayVertexBuffers) getProcAddress("glVertexArrayVertexBuffers");
    glVertexArrayAttribBinding = (_glVertexArrayAttribBinding) getProcAddress("glVertexArrayAttribBinding");
    glVertexArrayAttribFormat = (_glVertexArrayAttribFormat) getProcAddress("glVertexArrayAttribFormat");
    glVertexArrayAttribIFormat = (_glVertexArrayAttribIFormat) getProcAddress("glVertexArrayAttribIFormat");
    glVertexArrayAttribLFormat = (_glVertexArrayAttribLFormat) getProcAddress("glVertexArrayAttribLFormat");
    glVertexArrayBindingDivisor = (_glVertexArrayBindingDivisor) getProcAddress("glVertexArrayBindingDivisor");
    glGetVertexArrayiv = (_glGetVertexArrayiv) getProcAddress("glGetVertexArrayiv");
    glGetVertexArrayIndexediv = (_glGetVertexArrayIndexediv) getProcAddress("glGetVertexArrayIndexediv");
    glGetVertexArrayIndexed64iv = (_glGetVertexArrayIndexed64iv) getProcAddress("glGetVertexArrayIndexed64iv");
    glCreateSamplers = (_glCreateSamplers) getProcAddress("glCreateSamplers");
    glCreateProgramPipelines = (_glCreateProgramPipelines) getProcAddress("glCreateProgramPipelines");
    glCreateQueries = (_glCreateQueries) getProcAddress("glCreateQueries");
    glGetQueryBufferObjecti64v = (_glGetQueryBufferObjecti64v) getProcAddress("glGetQueryBufferObjecti64v");
    glGetQueryBufferObjectiv = (_glGetQueryBufferObjectiv) getProcAddress("glGetQueryBufferObjectiv");
    glGetQueryBufferObjectui64v = (_glGetQueryBufferObjectui64v) getProcAddress("glGetQueryBufferObjectui64v");
    glGetQueryBufferObjectuiv = (_glGetQueryBufferObjectuiv) getProcAddress("glGetQueryBufferObjectuiv");
    glMemoryBarrierByRegion = (_glMemoryBarrierByRegion) getProcAddress("glMemoryBarrierByRegion");
    glGetTextureSubImage = (_glGetTextureSubImage) getProcAddress("glGetTextureSubImage");
    glGetCompressedTextureSubImage = (_glGetCompressedTextureSubImage) getProcAddress("glGetCompressedTextureSubImage");
    glGetGraphicsResetStatus = (_glGetGraphicsResetStatus) getProcAddress("glGetGraphicsResetStatus");
    glGetnCompressedTexImage = (_glGetnCompressedTexImage) getProcAddress("glGetnCompressedTexImage");
    glGetnTexImage = (_glGetnTexImage) getProcAddress("glGetnTexImage");
    glGetnUniformdv = (_glGetnUniformdv) getProcAddress("glGetnUniformdv");
    glGetnUniformfv = (_glGetnUniformfv) getProcAddress("glGetnUniformfv");
    glGetnUniformiv = (_glGetnUniformiv) getProcAddress("glGetnUniformiv");
    glGetnUniformuiv = (_glGetnUniformuiv) getProcAddress("glGetnUniformuiv");
    glReadnPixels = (_glReadnPixels) getProcAddress("glReadnPixels");
    glTextureBarrier = (_glTextureBarrier) getProcAddress("glTextureBarrier");
}

#endif // _INFERNO_GL_H_