/*
 * %W% %E%
 *
 * Copyright  1990-2006 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation. 
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt). 
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA 
 * 
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions. 
 */

package com.sun.jump.module.windowing;

import com.sun.jump.common.JUMPWindow;
import com.sun.jump.module.JUMPModule;

/**
 * <code>JUMPWindowingModule</code> provides the ability to handle
 * basic window management tasks.
 */
public interface JUMPWindowingModule extends JUMPModule {
    /**
     * Returns all managed windows
     */
    public JUMPWindow[] getWindows();

    /**
     * Returns the current foreground window
     */
    public JUMPWindow getForeground();

    /**
     * @param window The window to give the foreground to
     */
    public void setForeground(JUMPWindow window);

    /**
     * @param window The window to put in the background
     */
    public void setBackground(JUMPWindow window);

    /**
     * Put the next eligible window in the foreground
     * Returns the new foreground window
     */
    public JUMPWindow nextWindow();

    /** 
     * Find JUMPWindow instace from window ID
     */
    public JUMPWindow idToWindow(long id);
}
