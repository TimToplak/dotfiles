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
	softwareHwnd := DllCall("GetWindow", "uint", softwareHwnd, "uint", 2)
	softwareHwnd := DllCall("GetWindow", "uint", softwareHwnd, "uint", 2)
	Return softwareHwnd
}

; Send a key to a software.
sendKeyToSoftware(processExe, key, method) {
	softwareHwnd := getsoftwareHwnd(processExe)
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


#!p::			sendKeyToSoftware("spotify.exe", "{Space}", "PostMessage") 		; Spotify: Play/Pause
#!Down::		sendKeyToSoftware("spotify.exe", "^{Right}", "PostMessage") 	; Spotify: Next
#!Up::			sendKeyToSoftware("spotify.exe", "^{Left}", "PostMessage") 		; Spotify: Previous
#!Right::		sendKeyToSoftware("spotify.exe", "+{Right}", "PostMessage") 	; Spotify: Seek forward
#!Left::		sendKeyToSoftware("spotify.exe", "+{Left}", "PostMessage") 		; Spotify: Seek backward
F14::	sendKeyToSoftware("spotify.exe", "^{Up}", "ControlSend") 		; Spotify: Volume up
F15::	sendKeyToSoftware("spotify.exe", "^{Down}", "ControlSend") 		; Spotify: Volume down

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