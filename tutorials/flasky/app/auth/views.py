
from flask              import render_template, redirect, request
from flask              import url_for, flash

from flask.ext.login    import login_user, logout_user, login_required

from .                  import auth
from ..models           import XUser
from .forms             import XLoginForm, XRegistrationForm


@auth.route( "/login/", methods=[ "GET", "POST" ] )
def Login():
    form = XLoginForm()
    if form.validate_on_submit():
        user = XUser.query.filter_by( email=form.email.data ).first()
        if user is not None and user.VerifyPassword( form.password.data ):
            login_user( user, form.remember_me.data )
            return redirect( request.args.get( "next" ) or url_for( "main.Index" ) )
        flash( "Invalid username or password" )
    return render_template( "auth/login.html", form=form )


@auth.route( "/register/", methods=[ "GET", "POST" ] )
def Register():
    form = XRegistrationForm()
    if form.validate_on_submit():
        user = XUser()
        user.email = form.email.data
        user.username = form.username.data
        user.password = form.password.data
        db.session.add( user )
        db.session.commit()
        flash( "You can now login." )
        return redirect( url_for( "auth.Login" ) )
    return render_template( "auth/register.html", form=form )


@auth.route( "/logout/" )
@login_required
def Logout():
    logout_user()
    flash( "You have been logged out." )
    return redirect( url_for( "main.Index" ) )

