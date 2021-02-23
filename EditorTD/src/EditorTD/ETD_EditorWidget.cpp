#include "EditorTD/ETD_EditorWidget.h"
#include "EditorTD/config.h"
#include <cmath>
ETD::Widgets::TextEditor::TextEditor(sf::RenderWindow* hwnd, const sf::FloatRect& bound)
{
	this->Init(hwnd, bound, true);

	_fontlib = new ETD::Util::FontLib();
	_text_string = sf::String("<function decriptions>");

	_text_object.setString(_text_string);
	_text_object.setFont(*_fontlib->GetFont(DEFAULT_FONT));
	_text_object.setCharacterSize(18);
	_text_object.setFillColor(Col_EDIT_TEXT);
	_text_object.setPosition(this->GetClientPivot_f());

	CacheTexture();
}

/*[Instruction for Children of Widgets]
*
*	- 1. process any events here.
	void UserUpdate(sf::Event* event) {}

	- 2. use buffer draw field: in init(), set has_buffer to `true`
	void BufferDrawField()
	{
		_buffer_renderer.draw( <geometry> );
	}

	- 3. any extra draw calls will use this function, overlay on top of widgets
	void ExtraDraw()
	{
		_hwnd->draw( <geometry> );
	}

	-4. `sf::IntRec _mask` stores the client region for drawing the buffer.
	-4.1 if want to move the text region, simply update _mask_offset_x, and y.
*/


void ETD::Widgets::TextEditor::ExtraDraw() {}

void ETD::Widgets::TextEditor::BufferDrawField()
{
	//sf::RectangleShape shape(sf::Vector2f(30,30));
	//shape.setFillColor(sf::Color::Red);
	//_buffer_renderer.draw(shape);

	_buffer_renderer.draw(_text_object);
}

void ETD::Widgets::TextEditor::UserUpdate(sf::Event* event)
{
	if (event->type == sf::Event::TextEntered)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
		{
			if (!_text_string.isEmpty()) _text_string.erase(_text_string.getSize() - 1);
			_text_object.setString(_text_string);
			Update_TypingOffset();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			_text_string += "\n";
			_text_object.setString(_text_string);
			//Explicit setting enter->
			_mask_offset_x = 0;
			_text_object.setPosition(_mask_offset_x, _mask_offset_y);
		}
		else
		{
			_text_string += event->text.unicode;
			_text_object.setString(_text_string);
			Update_TypingOffset();
		}
		
	}
	if (_text_object.getLocalBounds().width + _text_object.getLetterSpacing() > _mask.width) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
				_mask_offset_x -= 9;
				_mask_offset_x = (float)fmax(_mask.width -_text_object.getLocalBounds().width - _text_object.getLetterSpacing(), _mask_offset_x);
				_text_object.setPosition(_mask_offset_x, _mask_offset_y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
				_mask_offset_x += 9;
				_mask_offset_x = (float)fmin(0, _mask_offset_x);
				_text_object.setPosition(_mask_offset_x, _mask_offset_y);
		}
	}
}


void ETD::Widgets::TextEditor::Update_TypingOffset() 
{
	if(_text_string.getSize()>2)
	{
		_mask_offset_x = (float)fmin(0,
			_mask.width -
			(2.0f * _text_object.findCharacterPos(_text_string.getSize() - 1).x)
			+ _text_object.findCharacterPos(_text_string.getSize() - 2).x
			+ _text_object.getGlobalBounds().left
		);
		_text_object.setPosition(_mask_offset_x, _mask_offset_y);
	}

}