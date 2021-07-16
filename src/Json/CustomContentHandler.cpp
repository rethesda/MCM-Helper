#include "Json/CustomContentHandler.h"

CustomContentHandler::CustomContentHandler(CustomContent* customContent) :
	_customContent{ customContent }
{
}

bool CustomContentHandler::Complete()
{
	return _state == State::End;
}

bool CustomContentHandler::Int(int i)
{
	switch (_state) {
	case State::X:
		_customContent->X = static_cast<float>(i);
		_state = State::Start;
		return true;
	case State::Y:
		_customContent->Y = static_cast<float>(i);
		_state = State::Start;
		return true;
	default:
		return false;
	}
}

bool CustomContentHandler::Uint(unsigned i)
{
	switch (_state) {
	case State::X:
		_customContent->X = static_cast<float>(i);
		_state = State::Start;
		return true;
	case State::Y:
		_customContent->Y = static_cast<float>(i);
		_state = State::Start;
		return true;
	default:
		return false;
	}
}

bool CustomContentHandler::Double(double d)
{
	switch (_state) {
	case State::X:
		_customContent->X = static_cast<float>(d);
		_state = State::Start;
		return true;
	case State::Y:
		_customContent->Y = static_cast<float>(d);
		_state = State::Start;
		return true;
	default:
		return false;
	}
}

bool CustomContentHandler::String(
	const Ch* str,
	[[maybe_unused]] SizeType length,
	[[maybe_unused]] bool copy)
{
	switch (_state) {
	case State::Source:
		_customContent->Source = str;
		_state = State::Start;
		return true;
	default:
		return false;
	}
}

bool CustomContentHandler::StartObject()
{
	switch (_state) {
	case State::End:
		_state = State::Start;
		return true;
	default:
		return false;
	}
}

bool CustomContentHandler::Key(
	const Ch* str,
	[[maybe_unused]] SizeType length,
	[[maybe_unused]] bool copy)
{
	switch (_state) {
	case State::Start:
		if (strcmp(str, "source") == 0) {
			_state = State::Source;
			return true;
		}
		else if (strcmp(str, "x") == 0) {
			_state = State::X;
			return true;
		}
		else if (strcmp(str, "y") == 0) {
			_state = State::Y;
			return true;
		}
		else {
			return false;
		}
	default:
		return false;
	}
}

bool CustomContentHandler::EndObject([[maybe_unused]] SizeType memberCount)
{
	switch (_state) {
	case State::Start:
		_state = State::End;
		return true;
	default:
		return false;
	}
}