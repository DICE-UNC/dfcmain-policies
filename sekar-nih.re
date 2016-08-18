acPostProcForPut {
# send e-mail when a file is put into the named collection
 *Col = "/dfcmain/home/sekar/HealthWG";
 *AddHL = "howard@renci.org";
 *AddCS = "cschmitt@renci.org";
 *AddAR = "sekar@renci.org";
 msiSplitPath ($objPath, *Coll, *File);
#if (*Coll == *Col) {
 if (*Coll like *Col++"*") {
   msiSendMail (*AddHL, "Added file *File", "File added by $userNameClient to *Col");
   msiSendMail (*AddCS, "Added file *File", "File added by $userNameClient to *Col");
   msiSendMail (*AddAR, "Added file *File", "File added by $userNameClient to *Col");
 }

 # add this here for now - versioning for Operations stuff
 *VCol = "/dfcmain/home/dfcAdmin/FacilitiesAndOperations";
 msiWriteRodsLog(*VCol,*Status);
 if (*Coll like *VCol++"*") {
   *DesColl = *Coll ++ "/archives";

   # create the archice collection, if it doesn't exist
    *out = errormsg(msiCollCreate(*DesColl, 0, *Status), *Msg);

   # construct version name
   msiGetSystemTime(*Tim, "human");
                    
   # check whether there is a file extension on the name
   *Path = "*Coll/*File";
   *Head = *File;
   *End = "";
   *out = errormsg(msiSplitPathByKey (*File, ".", *Head, *End), *Msg);
   if (*End == "") { *Vers = *Head ++ "." ++ "*Tim"; }
   else {  *Vers = *Head ++ "." ++ "*Tim." ++ *End; }
   *Pathver = *DesColl ++ "/" ++ *Vers;

   # copy just iputted data object to archive collection
   msiDataObjCopy(*Path,*Pathver, "forceFlag=",*Status);
 }
}
