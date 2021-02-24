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

	//text cursor attributes
	_cursor_geo.setSize(sf::Vector2f(3,20));
	_cursor_geo.setFillColor(sf::Color::White);
	Update_InsertionPoint();

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


void ETD::Widgets::TextEditor::ExtraDraw() 
{
	
}

void ETD::Widgets::TextEditor::BufferDrawField()
{
	_buffer_renderer.draw(_text_object);
	_buffer_renderer.draw(_cursor_geo);
}

void ETD::Widgets::TextEditor::UserUpdate(sf::Event* event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Update_InsertionPoint(true);
		//Copy to moving.
		//_mask_offset_x -= 9;
		//_mask_offset_x = (float)fmax(_mask.width -_text_object.getLocalBounds().width - _text_object.getLetterSpacing(), _mask_offset_x);
		//_text_object.setPosition(_mask_offset_x, _mask_offset_y);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Update_InsertionPoint(false);
		std::cout << _insertion_point << std::endl;
		//_mask_offset_x += 9;
		//_mask_offset_x = (float)fmin(0, _mask_offset_x);
		//_text_object.setPosition(_mask_offset_x, _mask_offset_y);
		return;
	}

	if (event->type == sf::Event::TextEntered)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
		{
			if (!_text_string.isEmpty()) _text_string.erase(_insertion_point);
			_text_object.setString(_text_string);
			
			Update_TypingOffset();
			Update_InsertionPoint(false);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (_insertion_point == _text_string.getSize() - 1 || _insertion_point == -1)
			{
				_text_string += "\n";
			}
			else
			{
				_text_string.insert(_insertion_point + 1, "\n");
			}
			_text_object.setString(_text_string);
			
			//Explicit setting enter->
			_mask_offset_x = 0;
			_text_object.setPosition(_mask_offset_x, _mask_offset_y);
			Update_InsertionPoint_Enter();
		}
		else
		{
			if (_insertion_point == _text_string.getSize()-1 ||  _text_string.getSize() == 0)
			{
				_text_string += event->text.unicode;
				Update_InsertionPoint();
			}
			else
			{
				_text_string.insert(_insertion_point + 1, event->text.unicode);
				Update_InsertionPoint(true);
			}
			
			_text_object.setString(_text_string);
			Update_TypingOffset();
			Set_CursorLocation();
		}
	}
	//if (_text_object.getLocalBounds().width + _text_object.getLetterSpacing() > _mask.width) {

	//}
}


void ETD::Widgets::TextEditor::Update_TypingOffset() 
{
	if(_text_string.getSize()>=2)
	{
		_mask_offset_x = (float)fmin(0,
			_mask.width -
			_text_object.findCharacterPos(_text_string.getSize() - 1).x - Get_LetterDistance()*2
			+ _text_object.getGlobalBounds().left
		);
		_text_object.setPosition(_mask_offset_x, _mask_offset_y);
	}

}

void ETD::Widgets::TextEditor::Update_InsertionPoint(bool dir) 
{
	_insertion_point += dir ? 1 : -1;
	_insertion_point = (int)fmin(_insertion_point, _text_string.getSize() - 1);
	_insertion_point = (int)fmax(_insertion_point, -1);
	Set_CursorLocation();
}

void ETD::Widgets::TextEditor::Update_InsertionPoint()
{
	_insertion_point = _text_string.getSize() - 1;
	Set_CursorLocation();
}

void ETD::Widgets::TextEditor::Update_InsertionPoint_Enter()
{
	//BUG here
	_insertion_point += 2;
	_insertion_point = (int)fmin(_insertion_point, _text_string.getSize() - 1);
	_insertion_point = (int)fmax(_insertion_point, 0);
	sf::Vector2f loc = _text_object.findCharacterPos(_insertion_point);

	if (_insertion_point == _text_string.getSize() - 1) {
		loc.x = 0;
		loc.y += _text_object.getCharacterSize() + _text_object.getLineSpacing();
	}
	
	_cursor_geo.setPosition(loc);
}

void ETD::Widgets::TextEditor::Set_CursorLocation() 
{
	sf::Vector2f loc;
	if (_insertion_point >= 0)
	{
		loc = _text_object.findCharacterPos(_insertion_point);
		loc.x += Get_LetterDistance();
	}
	else 
	{
		loc.y = 0;
		loc.x = 0;
	}
	_cursor_geo.setPosition(loc);
}



float ETD::Widgets::TextEditor::Get_LetterDistance() 
{
	if (_text_string.getSize() >= 2)
	{
		return _text_object.findCharacterPos(_text_string.getSize() - 1).x - _text_object.findCharacterPos(_text_string.getSize() - 2).x;
	}
	else if (_text_string.getSize() == 1)
	{
		return _text_object.getGlobalBounds().width;
	}
	else return 0.f;
}