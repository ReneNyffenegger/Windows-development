using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;


public delegate bool WNDENUMPROC(
   UInt32    hWnd,
   IntPtr    lParam
);

internal static class WinAPI {

   [DllImport("user32.dll")]
    internal static extern bool EnumWindows(
       WNDENUMPROC cb          ,              // WNDENUMPROC lpEnumFiunc
       IntPtr      manageObject               // LPARAM      lParam (the managed object))
    );

   [DllImport("user32.dll", CharSet = CharSet.Auto)]
    internal static extern bool GetWindowText(
       UInt32        hWnd ,
       StringBuilder title,
       int           size
    );
}

public class WindowEnumerator {

    public static void Main() {

        List<UInt32> hWnds = new List<UInt32>();

     //
     // Prevent the managed object (hWnds) from being collected
     // by the garbage collector:
     //
        GCHandle    objHandle = GCHandle.Alloc(hWnds);

     //
     // Create an instance of a delegate in order to
     // provide a «callback» for EnumWindows:
     //
        WNDENUMPROC enumProc  = new WNDENUMPROC(callback);

     //
     // Get an internal representation for the gc handle
     // so as to be able to pass it to the second parameter
     // of EnumWindows:
     //
        IntPtr objHandlePtr = GCHandle.ToIntPtr(objHandle);

        WinAPI.EnumWindows( // Let Windows iterate over each window and
           enumProc    ,    // call enumProc (which is «initialized» for the method callback)
           objHandlePtr     // and pass this pointer to the method
        );

     //
     // Free the handle of the object so that
     // the object can be collected and
     // thus to prevent memory leaks:
     //
        objHandle.Free();

        StringBuilder title  = new StringBuilder(256);

        foreach (UInt32 hWnd in hWnds) {
           WinAPI.GetWindowText(hWnd, title, 256);
           Console.WriteLine("  {0,-8}: {1}", hWnd, title);
        }
    }

    private static bool callback(
    //
    // After calling WinAPI.EnumWindows, Windows calls
    // this method for each Window and passes it
    // the hWnd of the respective Window and
    // the value that was given as second parameter
    // to EnumWindows (objHandlePtr);
    //
       UInt32    hWnd,
       IntPtr    objHandlePtr
    ) {

     //
     // Get the handle to the object from the pointer:
     //
        GCHandle   objHandle =  GCHandle.FromIntPtr(objHandlePtr);

     //
     // and cast the handle's target into the underlying
     // managed object:
     //
        List<UInt32> obj = (List<UInt32>) objHandle.Target;
        obj.Add(hWnd);

        return true;
    }
}
