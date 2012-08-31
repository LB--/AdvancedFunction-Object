// --------------------------------
// Condition menu
// --------------------------------

#ifdef CONDITION_MENU

	SEPARATOR
	ITEM(0, "On Function")
	ITEM(1, "Call Function")

#endif

// --------------------------------
// Action menu
// --------------------------------

#ifdef ACTION_MENU

	// You have access to edPtr and you can throw in normal C++
	// code wherever you want in any of these menus. If you want to
	// show certain conditions based on a property (a la OINC socket)
	// use the property's value stored in edPtr:

	// if(edPtr->ShowAdvancedOptions)
	// {
	//		SUB_START("Bake pie")
	//			ITEM(0, "Apple pie")
	//			ITEM(1, "Mince pie")
	//		SUB_END
	// }
	// else
	// {
	//		ITEM(0, "Bake apple pie")
	// }

	// You could do some pretty cool stuff with this, like loading a
	// menu from an external source (ActiveX object?)

	// for(int i=0;i<edPtr->ActionCount;i++)
	//		ITEM(i,edPtr->Actions[i])

	// This will run every time the menu is opened in MMF2, so don't
	// make it too slow or it could get annoying

	SEPARATOR
	ITEM(1, "Add/Set Integer Parameter")
	ITEM(2, "Add/Set Float Parameter")
	ITEM(0, "Add/Set String Parameter")
	SEPARATOR
	ITEM(3, "Call Function")
	SEPARATOR
	ITEM(4, "Set Integer Return Value")
	ITEM(5, "Set Float Return Value")
	ITEM(6, "Set String Return Value")
	SEPARATOR

#endif


// --------------------------------
// Expression menu
// --------------------------------

#ifdef EXPRESSION_MENU

	SEPARATOR
	ITEM(7, "Get Integer Parameter")
	ITEM(8, "Get Float Parameter")
	ITEM(9, "Get String Parameter")
	SEPARATOR
	ITEM(10,"Get Integer Return Value")
	ITEM(11,"Get Float Return Value")
	ITEM(12,"Get String Return Value")
	SEPARATOR
	ITEM(13,"Set Integer Parameter")
	ITEM(14,"Set Integer Parameter$")
	ITEM(15,"Set Float Parameter")
	ITEM(16,"Set Float Parameter$")
	ITEM(17,"Set String Parameter")
	ITEM(18,"Set String Parameter$")
	SEPARATOR
	ITEM(4, "Call Integer Function")
	ITEM(5, "Call Float Function")
	ITEM(6, "Call String Function")
	SEPARATOR
	ITEM(0, "Get Name of Current Function")
	ITEM(1, "Get Number of Integer Parameters")
	ITEM(2, "Get Number of Float Parameters")
	ITEM(3, "Get Number of String Parameters")
	SEPARATOR

#endif