
#pragma once

#include "../framework/includes.h"
#include "../library/vector2.h"
#include "../framework/event.h"

class Control
{

	protected:
		Control* owningControl;
		Control* focusedChild;
		bool mouseInside;
		bool mouseDepressed;
		Vector2 resolvedLocation;

		void PreRender();
		void PostRender();
		void SetFocus(Control* Child);
		bool IsFocused();

		void ResolveLocation();
		void ConfigureFromXML( tinyxml2::XMLElement* Element );

	public:
		std::string Name;
		Vector2 Location;
		Vector2 Size;
		ALLEGRO_COLOR BackgroundColour;

		std::vector<Control*> Controls;

		Control(Control* Owner);
		virtual ~Control();

		Control* GetActiveControl();
		void Focus();

		virtual void EventOccured(Event* e);
		virtual void Render();
		virtual void Update();

};
