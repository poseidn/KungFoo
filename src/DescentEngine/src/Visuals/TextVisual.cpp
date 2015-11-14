#include "TextVisual.h"
/*
 *
 * gives link error on android when using this code here
void TextVisual::update(ScreenTransform const& trans, Vector2 const& pos) {

	logging::Info() << "Generating Text for " << m_text;

	m_uvBuffer.clear();
	m_vertexBuffer.clear();

	const float zPos = 1.0f;
	const Vector2 fontSpacing(0.6f, 1.0f);

	for (unsigned int i = 0; i < m_text.size(); i++) {
		Vector2 vertex_up_left = Vector2(pos.x() + i * fontSpacing.x(), pos.y() + fontSpacing.y());
		Vector2 vertex_bottom_right = Vector2(pos.x() + i * fontSpacing.x() + fontSpacing.x(), pos.y());

		vertex_up_left = trans.vectorToScreen(vertex_up_left);
		vertex_bottom_right = trans.vectorToScreen(vertex_bottom_right);

		// Trig 1
		m_vertexBuffer.push_back(vertex_up_left.x());
		m_vertexBuffer.push_back(-vertex_up_left.y());
		m_vertexBuffer.push_back(zPos);

		m_vertexBuffer.push_back(vertex_up_left.x());
		m_vertexBuffer.push_back(-vertex_bottom_right.y());
		m_vertexBuffer.push_back(zPos);

		m_vertexBuffer.push_back(vertex_bottom_right.x());
		m_vertexBuffer.push_back(-vertex_up_left.y());
		m_vertexBuffer.push_back(zPos);

		// Trig 2
		m_vertexBuffer.push_back(vertex_bottom_right.x());
		m_vertexBuffer.push_back(-vertex_bottom_right.y());
		m_vertexBuffer.push_back(zPos);

		m_vertexBuffer.push_back(vertex_bottom_right.x());
		m_vertexBuffer.push_back(-vertex_up_left.y());
		m_vertexBuffer.push_back(zPos);

		m_vertexBuffer.push_back(vertex_up_left.x());
		m_vertexBuffer.push_back(-vertex_bottom_right.y());
		m_vertexBuffer.push_back(zPos);

		char character = m_text[i];
		const float uv_x = (character % 16) / 16.0f;
		const float uv_y = (character / 16) / 16.0f;
		const float sizeChar = 1.0f / 16.0f;
		Vector2 uv_up_left(uv_x, uv_y);
		Vector2 uv_up_right(uv_x + sizeChar, uv_y);
		Vector2 uv_down_right(uv_x + sizeChar, uv_y + sizeChar);
		Vector2 uv_down_left(uv_x, uv_y + sizeChar);

		uv_up_left.addToList(m_uvBuffer);
		uv_down_left.addToList(m_uvBuffer);
		uv_up_right.addToList(m_uvBuffer);

		uv_down_right.addToList(m_uvBuffer);
		uv_up_right.addToList(m_uvBuffer);
		uv_down_left.addToList(m_uvBuffer);

	}

}*/
