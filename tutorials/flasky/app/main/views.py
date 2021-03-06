
from flask              import render_template, redirect, url_for
from flask              import abort, flash
from flask.ext.login    import login_required, current_user

from .                  import main
from .forms             import XEditProfileForm, XEditProfileAdminForm, XPostForm
from ..                 import db
from ..decorators       import AdminRequired
from ..models           import XUser, XRole, XPermission
from ..models           import XPost


@main.route( "/", methods=["GET", "POST"] )
def Index():
    form = XPostForm()
    if current_user.Can( XPermission.WRITE_ARTICLES ) and form.validate_on_submit():
        post = XPost()
        post.body = form.body.data
        post.author = current_user._get_current_object()

        db.session.add(post)
        db.session.commit()

        return redirect( url_for( ".Index" ) )
    posts = XPost.query.order_by( XPost.timestamp.desc() ).all()
    return render_template( "index.html", form=form, posts=posts, Permission=XPermission )


@main.route( "/user/<username>/" )
@login_required
def User( username ):
    user = XUser.query.filter_by( username=username ).first()
    if user is None:
        return abort( 404 )
    posts = user.posts.order_by( XPost.timestamp.desc() ).all()
    return render_template( "user.html", user=user, posts=posts )


@main.route( "/edit-profile/", methods=["GET", "POST"] )
@login_required
def EditProfile():
    form = XEditProfileForm()
    if form.validate_on_submit():
        current_user.name = form.name.data
        current_user.location = form.location.data
        current_user.about_me = form.about_me.data

        db.session.add( current_user )
        db.session.commit()

        flash( "Your profile has been updated." )
        return redirect( url_for( ".User", username=current_user.username ) )

    form.name.data = current_user.name
    form.location.data = current_user.location
    form.about_me.data = current_user.about_me
    return render_template( "edit_profile.html", form=form )


@main.route( "/edit-profile/<int:pk>/", methods=["GET", "POST"] )
@login_required
@AdminRequired
def EditProfileAdmin( pk ):
    user = XUser.query.get_or_404( pk )
    form = XEditProfileAdminForm( user=user )
    if form.validate_on_submit():
        user.email = form.email.data
        user.username = form.username.data
        user.confirmed = form.confirmed.data
        user.role = XRole.query.get( form.role.data )
        user.name = form.name.data
        user.location = form.location.data
        user.about_me = form.about_me.data

        db.session.add( user )
        db.session.commit()

        flash( "The profile has been updated." )
        return redirect( url_for( ".User", username=user.username ) )

    form.email.data = user.email
    form.username.data = user.username
    form.confirmed.data = user.confirmed
    form.role.data = user.role_pk
    form.name.data = user.name
    form.location.data = user.location
    form.about_me.data = user.about_me
    return render_template( "edit_profile.html", form=form, user=user )
