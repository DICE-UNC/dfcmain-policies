acPostProcForPut {
 # create a dated version of fileas soon as it is iputted
 *Col = "/dfcmain/home/dfcAdmin/FacilitiesAndOperations";
#if (*Coll == *Col) {
#if (*Coll like *Col++"*") {
 on($objPath like *Col++"*") {
   #*Coll = "/$rodsZoneClient/home/$userNameClient/*SourceColl";
   msiSplitPath ($objPath, *Coll, *File);
   *DestColl = $Coll ++ "/archives";
   msiCollCreate(*DestColl, 0, *Status);

   # construct version name
   msiGetSystemTime(*Tim, "human");
   
   # check whether there is a file extension on the name
   *Path = "*Coll/*File";
   *Head = *File;
   *End = "";
   *out = errormsg(msiSplitPathByKey (*File, ".", *Head, *End), *Msg);
   if (*End == "") { *Vers = *Head ++ "." ++ "*Tim"; }
   else {  *Vers = *Head ++ "." ++ "*Tim." ++ *End; }
   *Pathver = *DestColl ++ "/" ++ *Vers;

   # copy just iputted data object to archive collection
   msiDataObjCopy(*Path,*Pathver, "forceFlag=",*Status);
 }
}
