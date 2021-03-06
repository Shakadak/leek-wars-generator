/*
 * ColorModule.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: pierre
 */

#include "ColorModule.hpp"

const ls::LSClass* ColorModule::color_clazz;
const ColorType* const ColorModule::type = new ColorType();
const ls::Type ColorModule::type_ptr(ColorModule::type, ls::Nature::POINTER);

const Color* ColorModule::TRANSPARENT = new Color(0x00000000, true);
const Color* ColorModule::BLACK = new Color(0xff000000, true);
const Color* ColorModule::WHITE = new Color(0xffffffff, true);
const Color* ColorModule::RED = new Color(0xffff0000, true);
const Color* ColorModule::GREEN = new Color(0xff00ff00, true);
const Color* ColorModule::BLUE = new Color(0xff0000ff, true);

ls::Compiler::value Color_TRANSPARENT(ls::Compiler& c) { return c.new_pointer((void*) ColorModule::TRANSPARENT); }
ls::Compiler::value Color_BLACK(ls::Compiler& c) { return c.new_pointer((void*) ColorModule::BLACK); }
ls::Compiler::value Color_WHITE(ls::Compiler& c) { return c.new_pointer((void*) ColorModule::WHITE); }
ls::Compiler::value Color_RED(ls::Compiler& c) { return c.new_pointer((void*) ColorModule::RED); }
ls::Compiler::value Color_GREEN(ls::Compiler& c) { return c.new_pointer((void*) ColorModule::GREEN); }
ls::Compiler::value Color_BLUE(ls::Compiler& c) { return c.new_pointer((void*) ColorModule::BLUE); }

Color* color_rgb(int r, int g, int b) {

	Color* color = new Color();

	unsigned int red = (r << 16) & 0x00FF0000;
	unsigned int green = (g << 8) & 0x0000FF00;
	unsigned int blue = b & 0x000000FF;

	color->value = 0xFF000000 | red | green | blue;
	return color;
}

Color* color_rgba(int r, int g, int b, int a) {

	Color* color = new Color();

	unsigned int alpha = (a << 24) & 0xFF000000;
	unsigned int red = (r << 16) & 0x00FF0000;
	unsigned int green = (g << 8) & 0x0000FF00;
	unsigned int blue = b & 0x000000FF;

	color->value = alpha | red | green | blue;
	return color;
}

ColorModule::ColorModule() : Module("Color") {

	static_field("TRANSPARENT", ColorModule::type_ptr, (void*) &Color_TRANSPARENT);
	static_field("BLACK", ColorModule::type_ptr, (void*) &Color_BLACK);
	static_field("WHITE", ColorModule::type_ptr, (void*) &Color_WHITE);
	static_field("RED", ColorModule::type_ptr, (void*) &Color_RED);
	static_field("GREEN", ColorModule::type_ptr, (void*) &Color_GREEN);
	static_field("BLUE", ColorModule::type_ptr, (void*) &Color_BLUE);

	field("r", ls::Type::NUMBER);
	field("g", ls::Type::NUMBER);
	field("b", ls::Type::NUMBER);
	field("a", ls::Type::NUMBER);

	static_method("rgb", {
		{ColorModule::type_ptr, {ls::Type::INTEGER, ls::Type::INTEGER, ls::Type::INTEGER}, (void*) &color_rgb, ls::Method::NATIVE}
	});
	static_method("rgba", {
		{ColorModule::type_ptr, {ls::Type::INTEGER, ls::Type::INTEGER, ls::Type::INTEGER, ls::Type::INTEGER}, (void*) &color_rgba, ls::Method::NATIVE}
	});

	ColorModule::color_clazz = this->clazz;
}

ColorModule::~ColorModule() {}
