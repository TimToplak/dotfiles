;------------------------------------
; AUTOHOTKEY'S HOTKEYS :
;------------------------------------
; 	# = Windows Key
;	! = ALT
;------------------------------------

;------------------------------------
; COMMANDS SENT {} :
;------------------------------------
;	^ = CTRL
;------------------------------------


; Get the HWND of the software's main window.
getSoftwareHwnd(processExe) {
	WinGet, softwareHwnd, ID, ahk_exe %processExe%
	; We need the app's third top level window, so get next twice.
	; softwareHwnd := DllCall("GetWindow", "uint", softwareHwnd, "uint", 2)
	; softwareHwnd := DllCall("GetWindow", "uint", softwareHwnd, "uint", 2)
	Return softwareHwnd
}

getSoftwareHwndAtCord(x, y) {
	hWnd := DllCall("WindowFromPoint", "UInt64", x|(y << 32), "Ptr")    
	Return hWnd
}


; Send a key to a software.
sendKeyToSoftware(softwareHwnd, key, method) {
	if (method == "PostMessage" ) {
		PostMessage, 0x319,, 0xE0000,, ahk_id %softwareHwnd%
	}
	if (method == "ControlSend" ) {
		; Chromium ignores keys when it isn't focused.
		; Focus the document window without bringing the app to the foreground.
		ControlFocus, Chrome_RenderWidgetHostHWND1, ahk_id %softwareHwnd%
		ControlSend, , %key%, ahk_id %softwareHwnd%
	}
	Return
}

volume(type) {
	processName := "spotify.exe"
	WinGetTitle, winname, ahk_exe %processName%
	if (type == "up"){
		if (winname == "Spotify Premium" ) {
			softwareHwnd := getSoftwareHwndAtCord(1766, -1055)
			sendKeyToSoftware(softwareHwnd, "{Up}", "ControlSend")
		} else {
			softwareHwnd := getsoftwareHwnd("spotify.exe")
			sendKeyToSoftware(softwareHwnd, "^{Up}", "ControlSend")
		}
	}

	if (type == "down"){
		if (winname == "Spotify Premium" ) {
			softwareHwnd := getSoftwareHwndAtCord(1766, -1055)
			sendKeyToSoftware(softwareHwnd, "{Down}", "ControlSend")
		} else {
			softwareHwnd := getsoftwareHwnd("spotify.exe")
			sendKeyToSoftware(softwareHwnd, "^{Down}", "ControlSend")
		}
	}
	Return
}

; F14::	sendKeyToSoftware("spotify.exe", "^{Up}", "ControlSend") 		; Spotify: Volume up
; F15::	sendKeyToSoftware("spotify.exe", "^{Down}", "ControlSend") 		; Spotify: Volume down

F14::	volume("up")
F15::	volume("down")

; Win+alt+o: Show Spotify
#!o::
{
	softwareHwnd := getsoftwareHwnd("spotify.exe")
	WinGet, style, Style, ahk_id %softwareHwnd%
	if (style & 0x10000000) { ; WS_VISIBLE
		WinHide, ahk_id %softwareHwnd%
	} Else {
		WinShow, ahk_id %softwareHwnd%
		WinActivate, ahk_id %softwareHwnd%
	}
	Return
}